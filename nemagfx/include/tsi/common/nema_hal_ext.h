/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef NEMA_HAL_EXT_H__
#define NEMA_HAL_EXT_H__

#include <hal/nrf_gpu.h>
#include <hal/nrf_dispc.h>

typedef void (*gpu_event_cb_t) (nrf_gpu_event_t event, void* param);
typedef void (*dispc_event_cb_t) (nrf_dispc_event_t event, void* param);

void nema_register_callback(gpu_event_cb_t cb, void *pdata);
void nemadc_register_callback(dispc_event_cb_t cb, void *pdata);

#endif /* NEMA_HAL_EXT_H__ */
