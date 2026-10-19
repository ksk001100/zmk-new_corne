# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_DISPLAY AND CONFIG_NICE_VIEW_WIDGET_STATUS)
  if(NOT CONFIG_ZMK_SPLIT OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    message(FATAL_ERROR "nice_view_toyoterm is for the split peripheral; use nice_view on the central")
  endif()

  set(nice_view_upstream ${CMAKE_SOURCE_DIR}/boards/shields/nice_view)
  zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)
  # Reuse the active ZMK branch's status widget, battery and connection listeners.
  zephyr_library_sources(
    ${nice_view_upstream}/custom_status_screen.c
    ${nice_view_upstream}/widgets/bolt.c
    ${nice_view_upstream}/widgets/util.c
    ${nice_view_upstream}/widgets/peripheral_status.c
    art.c
  )
endif()
