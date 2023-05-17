#
# Copyright (c) 2022 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

if(NOT CONFIG_NEMA)
  return()
endif()

set(NEMA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(NEMA_HEADERS_BASE_DIR ${NEMA_DIR}/include/tsi)
set(NEMA_PLATFORM_DIR ${NEMA_DIR}/platforms/${CONFIG_NEMA_PLATFORM})

message(STATUS "NemaGFX platform: ${CONFIG_NEMA_PLATFORM}")

zephyr_interface_library_named(NEMA)

if(CONFIG_NEMAGUI_ENABLE)
  add_subdirectory(NemaGUI)
endif()

if(CONFIG_NEMAVG_ENABLE)
  add_subdirectory(NemaVG)
endif()

if(CONFIG_NEMA_PLATFORM_ZEPHYR_POSIX)
  add_subdirectory(NemaGFX_SW)
else()
  add_subdirectory(NemaGFX)
endif()

if(CONFIG_NEMADC_ENABLE)
  if(CONFIG_NEMA_PLATFORM_ZEPHYR_POSIX)
    add_subdirectory(NemaDC_SW)
  else()
    add_subdirectory(NemaDC)
  endif()
endif()

zephyr_link_libraries(NEMA)
