#
# Copyright (c) 2022 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

add_library(NemaVG INTERFACE)
target_include_directories(NemaVG INTERFACE
      ${NEMA_HEADERS_BASE_DIR}/common
      ${NEMA_HEADERS_BASE_DIR}/NemaGFX
      ${NEMA_HEADERS_BASE_DIR}/NemaVG
      )

target_link_libraries(NemaVG INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}/lib/libNemaVG.a)

target_link_libraries(NEMA INTERFACE NemaVG)
