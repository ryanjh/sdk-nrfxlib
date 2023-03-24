/*
 * Copyright (c) 2023 Nordic Semiconductor
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 *
 */

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include "psa/crypto.h"
#include <entropy_poll.h>

psa_status_t mbedtls_psa_external_get_random(
    mbedtls_psa_external_random_context_t *context,
    uint8_t *output, size_t output_size, size_t *output_length)
{
    int ret = mbedtls_hardware_poll(NULL,
                                    output,
                                    output_size,
                                    output_length);
    return ret == 0 ? PSA_SUCCESS : PSA_ERROR_HARDWARE_FAILURE;
}
