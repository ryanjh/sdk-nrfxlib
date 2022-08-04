#
# Copyright (c) 2022 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

add_library(NemaGUI INTERFACE)
target_include_directories(NemaGUI INTERFACE
      ${NEMA_HEADERS_BASE_DIR}/common
      ${NEMA_HEADERS_BASE_DIR}/NemaGFX
      ${NEMA_HEADERS_BASE_DIR}/NemaDC
      ${NEMA_HEADERS_BASE_DIR}/NemaGUI
      ${NEMA_HEADERS_BASE_DIR}/NemaGUI/gitems
      )

target_link_libraries(NemaGUI INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CONFIG_NEMA_PLATFORM}/libNemaGUI.a
      )

target_link_libraries(NEMA INTERFACE NemaGUI)
