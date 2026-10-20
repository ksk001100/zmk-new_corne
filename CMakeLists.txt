# SPDX-License-Identifier: MIT

if(CONFIG_SHIELD_NICE_VIEW AND CONFIG_ZMK_DISPLAY AND CONFIG_NICE_VIEW_WIDGET_STATUS)
  zephyr_library_named(nice_view_battery_percentage)
  zephyr_library_include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/boards/shields/nice_view/widgets
  )
  zephyr_library_sources(src/nice_view_battery.c)
  # Both upstream status widgets call draw_battery() from a separate source file.
  # Replace the battery drawing and shrink the header's right-aligned symbols,
  # retaining the upstream status widgets and their normal event listeners.
  zephyr_link_libraries(-Wl,--wrap=draw_battery -Wl,--wrap=init_label_dsc)
endif()
