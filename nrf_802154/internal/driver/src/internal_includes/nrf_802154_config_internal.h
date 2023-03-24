/*
 * Copyright (c) 2023, Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#ifndef NRF_802154_CONFIG_INTERNAL_H__
#define NRF_802154_CONFIG_INTERNAL_H__

#if defined(HALTIUM_XXAA) || defined(MOONLIGHT_XXAA)
#define NRF_802154_ENCRYPTION_ACCELERATOR_ECB 0
#endif

#endif // NRF_802154_CONFIG_INTERNAL_H__
