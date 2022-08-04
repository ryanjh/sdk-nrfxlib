#
# Copyright (c) 2023 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

add_library(NemaGFX INTERFACE)

target_include_directories(NemaGFX INTERFACE
      ${NEMA_HEADERS_BASE_DIR}/common
      ${NEMA_HEADERS_BASE_DIR}/NemaGFX
      )

target_link_libraries(NemaGFX INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}/lib/libNemaGFX.a)

target_link_libraries(NEMA INTERFACE NemaGFX)
