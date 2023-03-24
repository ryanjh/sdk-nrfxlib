#
# Copyright (c) 2023, Nordic Semiconductor ASA. All Rights Reserved.
#
# The information contained herein is confidential property of Nordic Semiconductor ASA.
# The use, copying, transfer or disclosure of such information is prohibited except by
# express written agreement with Nordic Semiconductor ASA.
#

add_subdirectory(zephyr)

target_include_directories(nrf-802154-driver-interface
  INTERFACE
    driver/src
    driver/src/internal_includes
)

target_sources(nrf-802154-driver
  PRIVATE
    driver/src/nrf_802154_aes_ccm_acc_ccm.c
)

target_compile_definitions(nrf-802154-platform
  PUBLIC
    NRF_802154_USE_INTERNAL_INCLUDES=1
)

target_include_directories(nrf-802154-platform
  PUBLIC
    sl/internal_includes
)
