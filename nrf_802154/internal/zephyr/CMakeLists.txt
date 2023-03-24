#
# Copyright (c) 2023, Nordic Semiconductor ASA. All Rights Reserved.
#
# The information contained herein is confidential property of Nordic Semiconductor ASA.
# The use, copying, transfer or disclosure of such information is prohibited except by
# express written agreement with Nordic Semiconductor ASA.
#

if (CONFIG_SOC_SERIES_NRF54HX OR CONFIG_SOC_PLATFORM_NRF54L)
  set(NRF54_SERIES 1)
endif()
