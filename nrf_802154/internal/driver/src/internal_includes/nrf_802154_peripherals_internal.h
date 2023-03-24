/*
 * Copyright (c) 2020 - 2023, Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#ifndef NRF_802154_PERIPHERALS_INTERNAL_H__
#define NRF_802154_PERIPHERALS_INTERNAL_H__

#if defined(HALTIUM_XXAA)
#include "nrf_802154_peripherals_nrf54h.h"
#elif defined(MOONLIGHT_XXAA)
#include "nrf_802154_peripherals_nrf54l.h"
#endif

#endif // NRF_802154_PERIPHERALS_INTERNAL_H__
