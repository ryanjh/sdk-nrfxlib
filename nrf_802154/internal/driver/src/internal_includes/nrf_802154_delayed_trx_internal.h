/*
 * Copyright (c) 2023, Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#ifndef NRF_802154_DELAYED_TRX_INTERNAL_H__
#define NRF_802154_DELAYED_TRX_INTERNAL_H__

#if defined(BOARD_FPGA) && defined(HALTIUM_XXAA)
#define TX_SETUP_TIME_MAX 1600u ///< Maximum time needed to prepare TX procedure [us]. It does not include TX ramp-up time.
#define RX_SETUP_TIME_MAX 1600u ///< Maximum time needed to prepare RX procedure [us]. It does not include RX ramp-up time.
#elif defined(HALTIUM_XXAA)
#define TX_SETUP_TIME_MAX 400u  ///< Maximum time needed to prepare TX procedure [us]. It does not include TX ramp-up time.
#define RX_SETUP_TIME_MAX 400u  ///< Maximum time needed to prepare RX procedure [us]. It does not include RX ramp-up time.
#elif defined(MOONLIGHT_XXAA)
#define TX_SETUP_TIME_MAX 600u  ///< Maximum time needed to prepare TX procedure [us]. It does not include TX ramp-up time.
#define RX_SETUP_TIME_MAX 600u  ///< Maximum time needed to prepare RX procedure [us]. It does not include RX ramp-up time.
#endif

#endif  // NRF_802154_DELAYED_TRX_INTERNAL_H__
