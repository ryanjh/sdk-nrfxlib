/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef NEMA_HAL_EXT_H__
#define NEMA_HAL_EXT_H__

#include <hal/nrf_gpu.h>

typedef void (*event_cb) (nrf_gpu_event_t event, void* param);

void nema_register_callback(event_cb cb, void *pdata);
void nema_gfx_enable(void);
void nema_gfx_disable(void);

#endif //NEMA_HAL_EXT_H__
