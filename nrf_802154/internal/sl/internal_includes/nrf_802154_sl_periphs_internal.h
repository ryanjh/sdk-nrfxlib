/*
 * Copyright (c) 2023, Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#ifndef NRF_802154_SL_PERIPHS_INTERNAL_H__
#define NRF_802154_SL_PERIPHS_INTERNAL_H__

#if defined(HALTIUM_XXAA)
#define NRF_802154_EGU_INSTANCE_NO 020
#elif defined(MOONLIGHT_XXAA)
#define NRF_802154_EGU_INSTANCE_NO 10
#endif

/**
 * @def NRF_802154_SL_DPPIC_INSTANCE_NO
 *
 * Id of the DPPIC instance used by the driver to connect peripherals to radio.
 *
 */
#if defined(HALTIUM_XXAA)
#define NRF_802154_SL_DPPIC_INSTANCE_NO 020
#elif defined(MOONLIGHT_XXAA)
#define NRF_802154_SL_DPPIC_INSTANCE_NO 10
#endif

/**
 * @def NRF_802154_SL_DPPIC_INSTANCE
 *
 * The DPPIC instance used by the driver to connect peripherals to radio.
 *
 */
#define NRF_802154_SL_DPPIC_INSTANCE NRFX_CONCAT_2(NRF_DPPIC, NRF_802154_SL_DPPIC_INSTANCE_NO)

#endif // NRF_802154_SL_PERIPHS_INTERNAL_H__
