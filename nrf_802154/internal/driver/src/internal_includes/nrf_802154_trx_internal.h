/*
 * Copyright (c) 2023, Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#ifndef NRF_802154_TRX_INTERNAL_H__
#define NRF_802154_TRX_INTERNAL_H__

#if defined(BOARD_FPGA) && defined(HALTIUM_XXAA)
#define NRF_802154_TRX_TEST_MODE_ALLOW_LATE_TX_ACK 1
#endif

#if defined(BOARD_FPGA) || defined(HALTIUM_XXAA)

#define NRF_802154_TRX_ENABLE_INTERNAL() nrf_802154_trx_enable_internal()

static inline void nrf_802154_trx_enable_internal(void)
{
#if defined(BOARD_FPGA)
    uint32_t temp;

    NRF_RADIO->QOVERRIDE27 = 0;
    temp                   = NRF_RADIO->DBCCORR & ~RADIO_DBCCORR_TH_Msk;
    NRF_RADIO->DBCCORR     = temp | (0x2d << RADIO_DBCCORR_TH_Pos);
    temp                   = NRF_RADIO->ADDRWINSIZE & ~RADIO_ADDRWINSIZE_IEEE802154_Msk;
    NRF_RADIO->ADDRWINSIZE = temp | (0x18 << RADIO_ADDRWINSIZE_IEEE802154_Pos);
#elif defined(HALTIUM_XXAA)
    uint32_t temp;

    NRF_RADIO->SPHYNXANA.FSCTRL0       = NRF_FICR->TRIM.RADIOCORE.RADIO.SPHYNXANA.FSCTRL0;
    NRF_RADIO->SPHYNXANA.FSCTRL1       = NRF_FICR->TRIM.RADIOCORE.RADIO.SPHYNXANA.FSCTRL1;
    NRF_RADIO->SPHYNXANA.FSCTRL2       = NRF_FICR->TRIM.RADIOCORE.RADIO.SPHYNXANA.FSCTRL2;
    NRF_RADIO->SPHYNXANA.RXCTRL        = NRF_FICR->TRIM.RADIOCORE.RADIO.SPHYNXANA.RXCTRL;
    NRF_RADIO->SPHYNXANA.OVRRXTRIMCODE = NRF_FICR->TRIM.RADIOCORE.RADIO.SPHYNXANA.OVRRXTRIMCODE;
    NRF_RADIO->RXAGC.CALIBRATION       = NRF_FICR->TRIM.RADIOCORE.RADIO.RXAGC.CALIBRATION;
    NRF_RADIO->EXPECTEDPVTTOTRATIO     = NRF_FICR->TRIM.RADIOCORE.RADIO.PVTTOT;
    NRF_RADIO->ESTKDTCVAL              = NRF_FICR->TRIM.RADIOCORE.RADIO.KDTC;
    NRF_RADIO->TXINTERFACEHFGAIN       = NRF_FICR->TRIM.RADIOCORE.RADIO.TXHFGAIN;
    NRF_RADIO->ADPLLSTARTUPCOMMAND6    = NRF_FICR->TRIM.RADIOCORE.RADIO.PVTTOFIX;

    NRF_RADIO->RXSYNC      = 0x3390;
    NRF_RADIO->ADDRWINSIZE = 0x1d111500;
    temp                   = NRF_RADIO->DBCCORR & ~RADIO_DBCCORR_TH_Msk;
    NRF_RADIO->DBCCORR     = temp | (0x51 << RADIO_DBCCORR_TH_Pos);
#endif

    nrf_radio_fast_ramp_up_enable_set(NRF_RADIO, true);
}

#endif // defined(BOARD_FPGA) || defined(HALTIUM_XXAA)

#if defined(HALTIUM_XXAA) || defined(MOONLIGHT_XXAA)

#define NRF_802154_TRX_RADIO_RESET_INTERNAL() nrf_802154_trx_radio_reset_internal()

static inline void nrf_802154_trx_radio_reset_internal(void)
{
    NRF_RADIO->TASKS_TXEN          = 0;
    NRF_RADIO->TASKS_RXEN          = 0;
    NRF_RADIO->TASKS_START         = 0;
    NRF_RADIO->TASKS_STOP          = 0;
    NRF_RADIO->TASKS_DISABLE       = 0;
    NRF_RADIO->TASKS_RSSISTART     = 0;
    NRF_RADIO->TASKS_BCSTART       = 0;
    NRF_RADIO->TASKS_BCSTOP        = 0;
    NRF_RADIO->TASKS_EDSTART       = 0;
    NRF_RADIO->TASKS_EDSTOP        = 0;
    NRF_RADIO->TASKS_CCASTART      = 0;
    NRF_RADIO->TASKS_CCASTOP       = 0;
    NRF_RADIO->SUBSCRIBE_TXEN      = 0;
    NRF_RADIO->SUBSCRIBE_RXEN      = 0;
    NRF_RADIO->SUBSCRIBE_START     = 0;
    NRF_RADIO->SUBSCRIBE_STOP      = 0;
    NRF_RADIO->SUBSCRIBE_DISABLE   = 0;
    NRF_RADIO->SUBSCRIBE_RSSISTART = 0;
    NRF_RADIO->SUBSCRIBE_BCSTART   = 0;
    NRF_RADIO->SUBSCRIBE_BCSTOP    = 0;
    NRF_RADIO->SUBSCRIBE_EDSTART   = 0;
    NRF_RADIO->SUBSCRIBE_EDSTOP    = 0;
    NRF_RADIO->SUBSCRIBE_CCASTART  = 0;
    NRF_RADIO->SUBSCRIBE_CCASTOP   = 0;
    NRF_RADIO->EVENTS_READY        = 0;
    NRF_RADIO->EVENTS_ADDRESS      = 0;
    NRF_RADIO->EVENTS_PAYLOAD      = 0;
    NRF_RADIO->EVENTS_END          = 0;
    NRF_RADIO->EVENTS_DISABLED     = 0;
    NRF_RADIO->EVENTS_DEVMATCH     = 0;
    NRF_RADIO->EVENTS_DEVMISS      = 0;
    NRF_RADIO->EVENTS_BCMATCH      = 0;
    NRF_RADIO->EVENTS_CRCOK        = 0;
    NRF_RADIO->EVENTS_CRCERROR     = 0;
    NRF_RADIO->EVENTS_FRAMESTART   = 0;
    NRF_RADIO->EVENTS_EDEND        = 0;
    NRF_RADIO->EVENTS_EDSTOPPED    = 0;
    NRF_RADIO->EVENTS_CCAIDLE      = 0;
    NRF_RADIO->EVENTS_CCABUSY      = 0;
    NRF_RADIO->EVENTS_CCASTOPPED   = 0;
    NRF_RADIO->EVENTS_RATEBOOST    = 0;
    NRF_RADIO->EVENTS_TXREADY      = 0;
    NRF_RADIO->EVENTS_RXREADY      = 0;
    NRF_RADIO->EVENTS_MHRMATCH     = 0;
    NRF_RADIO->EVENTS_PHYEND       = 0;
    NRF_RADIO->EVENTS_CTEPRESENT   = 0;
    NRF_RADIO->PUBLISH_READY       = 0;
    NRF_RADIO->PUBLISH_ADDRESS     = 0;
    NRF_RADIO->PUBLISH_PAYLOAD     = 0;
    NRF_RADIO->PUBLISH_END         = 0;
    NRF_RADIO->PUBLISH_DISABLED    = 0;
    NRF_RADIO->PUBLISH_DEVMATCH    = 0;
    NRF_RADIO->PUBLISH_DEVMISS     = 0;
    NRF_RADIO->PUBLISH_BCMATCH     = 0;
    NRF_RADIO->PUBLISH_CRCOK       = 0;
    NRF_RADIO->PUBLISH_CRCERROR    = 0;
    NRF_RADIO->PUBLISH_FRAMESTART  = 0;
    NRF_RADIO->PUBLISH_EDEND       = 0;
    NRF_RADIO->PUBLISH_EDSTOPPED   = 0;
    NRF_RADIO->PUBLISH_CCAIDLE     = 0;
    NRF_RADIO->PUBLISH_CCABUSY     = 0;
    NRF_RADIO->PUBLISH_CCASTOPPED  = 0;
    NRF_RADIO->PUBLISH_RATEBOOST   = 0;
    NRF_RADIO->PUBLISH_TXREADY     = 0;
    NRF_RADIO->PUBLISH_RXREADY     = 0;
    NRF_RADIO->PUBLISH_MHRMATCH    = 0;
    NRF_RADIO->PUBLISH_PHYEND      = 0;
    NRF_RADIO->PUBLISH_CTEPRESENT  = 0;
    NRF_RADIO->SHORTS              = 0;
    NRF_RADIO->INTENSET00          = 0;
    NRF_RADIO->INTENCLR00          = 0xffffffff;
    NRF_RADIO->PACKETPTR           = 0;
    NRF_RADIO->FREQUENCY           = 0;
    NRF_RADIO->TXPOWER             = 0;
    NRF_RADIO->MODE                = 0;
    NRF_RADIO->PCNF0               = 0;
    NRF_RADIO->PCNF1               = 0;
    NRF_RADIO->BASE0               = 0;
    NRF_RADIO->BASE1               = 0;
    NRF_RADIO->PREFIX0             = 0;
    NRF_RADIO->PREFIX1             = 0;
    NRF_RADIO->TXADDRESS           = 0;
    NRF_RADIO->RXADDRESSES         = 0;
    NRF_RADIO->CRCCNF              = 0;
    NRF_RADIO->CRCPOLY             = 0;
    NRF_RADIO->CRCINIT             = 0;
    NRF_RADIO->TIFS                = 0;
    NRF_RADIO->DATAWHITEIV         = 0;
    NRF_RADIO->BCC                 = 0;
    NRF_RADIO->DACNF               = 0;
    NRF_RADIO->MHRMATCHCONF        = 0;
    NRF_RADIO->MHRMATCHMASK        = 0;
    NRF_RADIO->SFD                 = 0xA7;
    NRF_RADIO->EDCTRL              = RADIO_EDCTRL_ResetValue;
    NRF_RADIO->CCACTRL             = 0x52D0000;
    NRF_RADIO->DFEMODE             = 0;
    NRF_RADIO->CTEINLINECONF       = 0x2800;
    NRF_RADIO->DFECTRL1            = 0x23282;
    NRF_RADIO->DFECTRL2            = 0;
    NRF_RADIO->SWITCHPATTERN       = 0;
    NRF_RADIO->CLEARPATTERN        = 0;
    NRF_RADIO->DFEPACKET.PTR       = 0;
    NRF_RADIO->DFEPACKET.MAXCNT    = 0x1000;

    for (uint8_t i = 0; i < 8; i++)
    {
        NRF_RADIO->DAB[i]          = 0;
        NRF_RADIO->DAP[i]          = 0;
        NRF_RADIO->PSEL.DFEGPIO[i] = 0xFFFFFFFF;
    }
}

#endif // defined(HALTIUM_XXAA) || defined(MOONLIGHT_XXAA)

#endif // NRF_802154_TRX_INTERNAL_H__
