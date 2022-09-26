/*
 * Copyright (c) 2021, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "nrf_802154_aes_ccm.h"
#include "nrf_802154_config.h"

#if NRF_802154_ACCELERATOR_CCM

#include <assert.h>
#include <string.h>

#include "hal/nrf_ccm.h"
#include "helpers/nrf_vdma.h"
#include "nrf_802154_const.h"
#include "nrf_802154_tx_work_buffer.h"
#include "nrf_802154_peripherals.h"
#include "nrf_802154_utils_byteorder.h"
#include "platform/nrf_802154_irq.h"

#define CCM_EMPTY_POINTER (void *)0x00000001

typedef struct
{
    struct
    {
        uint16_t alen;
        uint16_t mlen;
    } in;
    struct
    {
        uint16_t alen;
        uint8_t  mlen_lsb;
        uint8_t  mlen_msb;
    } out;
} ccm_params_t;

__ALIGN(4) static nrf_vdma_job_t in_job_list[5];  ///< CCM DMA input job list array.
__ALIGN(4) static nrf_vdma_job_t out_job_list[6]; ///< CCM DMA output job list array.

static ccm_params_t ccm_params;                   ///< CCM peripheral parameters.
static bool         m_initialized;                ///< Module init status.

static void ccm_disable(void)
{
    nrf_802154_irq_disable(nrfx_get_irq_number(NRF_CCM020));
    nrf_ccm_subscribe_clear(NRF_CCM020, NRF_CCM_TASK_START);
    nrf_ccm_subscribe_clear(NRF_CCM020, NRF_CCM_TASK_STOP);
    nrf_ccm_int_disable(NRF_CCM020, NRF_CCM_INT_ERROR_MASK | NRF_CCM_INT_END_MASK);
    nrf_ccm_disable(NRF_CCM020);
}

static void ccm_irq_handler(void)
{
    if (nrf_ccm_int_enable_check(NRF_CCM020, NRF_CCM_INT_ERROR_MASK) &&
        nrf_ccm_event_check(NRF_CCM020, NRF_CCM_EVENT_ERROR))
    {
        nrf_ccm_event_clear(NRF_CCM020, NRF_CCM_EVENT_ERROR);
        assert(false);
    }

    if (nrf_ccm_int_enable_check(NRF_CCM020, NRF_CCM_INT_END_MASK) &&
        nrf_ccm_event_check(NRF_CCM020, NRF_CCM_EVENT_END))
    {
        nrf_ccm_event_clear(NRF_CCM020, NRF_CCM_EVENT_END);
        nrf_802154_tx_work_buffer_is_secured_set();
        ccm_disable();
    }
}

static void u8_string_to_u32x4_big_endian(const uint8_t * p_input,
                                          uint8_t         input_len,
                                          uint32_t      * p_output)
{
    const uint8_t unaligned = input_len % sizeof(uint32_t);
    const uint8_t len       = unaligned > 0 ? unaligned : sizeof(uint32_t);
    const uint8_t shift     = (sizeof(uint32_t) - len) * 8;
    uint32_t      data      = big_32_to_host((uint8_t *)p_input);

    p_input    += len;
    data      >>= shift;
    p_output[3] = data;

    for (int i = 2; i >= 0; i--)
    {
        data        = big_32_to_host((uint8_t *)p_input);
        p_input    += sizeof(uint32_t);
        p_output[i] = data;
    }
}

static bool ccm_configure(const nrf_802154_aes_ccm_data_t * p_aes_ccm_data,
                          uint8_t                         * p_adata,
                          uint8_t                         * p_mdata)
{
    nrf_ccm_config_t ccm_config;
    nrf_ccm_maclen_t maclen;
    uint8_t          macsize;
    uint32_t         key[4];
    uint32_t         nonce[4];

    switch (p_aes_ccm_data->mic_level)
    {
        case SECURITY_LEVEL_MIC_32:
        case SECURITY_LEVEL_ENC_MIC_32:
            maclen  = NRF_CCM_MODE_MACLEN_M4;
            macsize = 4;
            break;

        case SECURITY_LEVEL_MIC_64:
        case SECURITY_LEVEL_ENC_MIC_64:
            maclen  = NRF_CCM_MODE_MACLEN_M8;
            macsize = 8;
            break;

        case SECURITY_LEVEL_MIC_128:
        case SECURITY_LEVEL_ENC_MIC_128:
            maclen  = NRF_CCM_MODE_MACLEN_M16;
            macsize = 16;
            break;

        default:
            return false;
    }

    ccm_config.mode       = NRF_CCM_MODE_ENCRYPTION;
    ccm_config.datarate   = NRF_CCM_DATARATE_250K;
    ccm_config.protocol   = NRF_CCM_MODE_PROTOCOL_IEEE802154;
    ccm_config.mac_length = maclen;

    u8_string_to_u32x4_big_endian(p_aes_ccm_data->key, sizeof(p_aes_ccm_data->key), key);
    u8_string_to_u32x4_big_endian(p_aes_ccm_data->nonce, sizeof(p_aes_ccm_data->nonce), nonce);

    // CCM peripheral job list integer params pointed by p_job_ptr must have big-endian byte order.
    host_16_to_little(p_aes_ccm_data->auth_data_len, (uint8_t*)&ccm_params.in.alen);
    host_16_to_little(p_aes_ccm_data->plain_text_data_len, (uint8_t*)&ccm_params.in.mlen);

    nrf_vdma_job_fill(&in_job_list[0], &ccm_params.in.alen, sizeof(ccm_params.in.alen), 0);
    nrf_vdma_job_fill(&in_job_list[1], &ccm_params.in.mlen, sizeof(ccm_params.in.mlen), 0);
    nrf_vdma_job_fill(&in_job_list[2], p_aes_ccm_data->auth_data, p_aes_ccm_data->auth_data_len, 0);
    nrf_vdma_job_fill(&in_job_list[3], p_aes_ccm_data->plain_text_data, p_aes_ccm_data->plain_text_data_len, 0);
    nrf_vdma_job_terminate(&in_job_list[4]);

    nrf_vdma_job_fill(&out_job_list[0], &ccm_params.out.alen, sizeof(ccm_params.out.alen), 0);
    nrf_vdma_job_fill(&out_job_list[1], &ccm_params.out.mlen_lsb, sizeof(ccm_params.out.mlen_lsb), 0);
    nrf_vdma_job_fill(&out_job_list[2], &ccm_params.out.mlen_msb, sizeof(ccm_params.out.mlen_msb), 0);
    nrf_vdma_job_fill(&out_job_list[3], p_adata, p_aes_ccm_data->auth_data_len, 0);
    nrf_vdma_job_fill(&out_job_list[4], p_mdata, p_aes_ccm_data->plain_text_data_len + macsize, 0);
    nrf_vdma_job_terminate(&out_job_list[5]);

    if (!m_initialized)
    {
        nrf_802154_irq_init(nrfx_get_irq_number(NRF_CCM020), NRF_802154_ECB_PRIORITY, ccm_irq_handler);
        m_initialized = true;
    }

    nrf_802154_irq_clear_pending(nrfx_get_irq_number(NRF_CCM020));
    nrf_802154_irq_enable(nrfx_get_irq_number(NRF_CCM020));

    nrf_ccm_enable(NRF_CCM020);
    nrf_ccm_configure(NRF_CCM020, &ccm_config);
    nrf_ccm_key_set(NRF_CCM020, key);
    nrf_ccm_nonce_set(NRF_CCM020, nonce);
    nrf_ccm_in_ptr_set(NRF_CCM020, in_job_list);
    nrf_ccm_out_ptr_set(NRF_CCM020, out_job_list);
    nrf_ccm_event_clear(NRF_CCM020, NRF_CCM_EVENT_ERROR);
    nrf_ccm_event_clear(NRF_CCM020, NRF_CCM_EVENT_END);
    nrf_ccm_int_enable(NRF_CCM020, NRF_CCM_INT_ERROR_MASK | NRF_CCM_INT_END_MASK);
    nrf_ccm_adatamask_set(NRF_CCM020, 0xff);

    nrf_ccm_subscribe_set(NRF_CCM020, NRF_CCM_TASK_START, NRF_802154_DPPI_RADIO_READY);
    nrf_ccm_subscribe_set(NRF_CCM020, NRF_CCM_TASK_STOP, NRF_802154_DPPI_RADIO_DISABLED);

    return true;
}

bool nrf_802154_aes_ccm_transform_prepare(const nrf_802154_aes_ccm_data_t * p_aes_ccm_data)
{
    uint8_t * p_work_buffer;
    uint8_t * p_ciphertext;

    // Verify that all necessary data is available
    if (p_aes_ccm_data->raw_frame == NULL)
    {
        return false;
    }

    // Verify that the optional data, if exists, is complete
    if (((p_aes_ccm_data->auth_data_len != 0) && (p_aes_ccm_data->auth_data == NULL)) ||
        ((p_aes_ccm_data->plain_text_data_len != 0) && (p_aes_ccm_data->plain_text_data == NULL)))
    {
        return false;
    }

    // Verify that the MIC level is valid
    if (p_aes_ccm_data->mic_level > SECURITY_LEVEL_MIC_LEVEL_MASK)
    {
        return false;
    }

    ptrdiff_t offset;

    if (p_aes_ccm_data->auth_data)
    {
        offset = p_aes_ccm_data->auth_data_len + PHR_SIZE;
    }
    else
    {
        offset = p_aes_ccm_data->raw_frame[PHR_OFFSET] + PHR_SIZE;
    }

    assert((offset >= 0) && (offset <= MAX_PACKET_SIZE + PHR_SIZE));

    nrf_802154_tx_work_buffer_plain_text_offset_set(offset);
    p_work_buffer = nrf_802154_tx_work_buffer_enable_for(p_aes_ccm_data->raw_frame);
    p_ciphertext  = p_work_buffer + offset;

    memcpy(p_work_buffer, p_aes_ccm_data->raw_frame, PHR_SIZE);
    memset(&p_work_buffer[PSDU_OFFSET], 0, p_aes_ccm_data->raw_frame[PHR_OFFSET]);

    return ccm_configure(p_aes_ccm_data, p_work_buffer + PHR_SIZE, p_ciphertext);
}

void nrf_802154_aes_ccm_transform_start(uint8_t * p_frame)
{
    // Intentionally empty
}

void nrf_802154_aes_ccm_transform_abort(uint8_t * p_frame)
{
    ccm_disable();
}

void nrf_802154_aes_ccm_transform_reset(void)
{
    // Intentionally empty
}

#endif // NRF_802154_CONFIG_ACCEL_CCM
