#
# Copyright (c) 2022 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

add_library(NemaDC INTERFACE)

target_include_directories(NemaDC INTERFACE
      ${NEMA_HEADERS_BASE_DIR}/common
      ${NEMA_HEADERS_BASE_DIR}/NemaDC
      )

target_link_libraries(NemaDC INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}/lib/libNemaDC.a)

target_link_libraries(NEMA INTERFACE NemaDC)
