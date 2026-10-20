/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include "util.h"

LV_IMG_DECLARE(bolt);

/* Linker wrapper shared by the central and peripheral nice!view widgets. */
void __wrap_draw_battery(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_rect_dsc_t background;
    init_rect_dsc(&background, LVGL_BACKGROUND);
    lv_draw_rect_dsc_t foreground;
    init_rect_dsc(&foreground, LVGL_FOREGROUND);

    /* Keep the original height and position; shorten the gauge to make room. */
    lv_canvas_draw_rect(canvas, 0, 2, 20, 12, &foreground);
    lv_canvas_draw_rect(canvas, 1, 3, 18, 10, &background);
    uint8_t battery = state->battery > 100 ? 100 : state->battery;
    uint8_t fill = (battery * 16 + 50) / 100;
    if (fill > 0) {
        lv_canvas_draw_rect(canvas, 2, 4, fill, 8, &foreground);
    }
    lv_canvas_draw_rect(canvas, 21, 5, 3, 6, &foreground);
    lv_canvas_draw_rect(canvas, 22, 6, 1, 4, &background);

    if (state->charging) {
        lv_draw_img_dsc_t image;
        lv_draw_img_dsc_init(&image);
        lv_canvas_draw_img(canvas, 4, -1, &bolt, &image);
    }

    /* Reserve x >= 51 for the existing connection/USB status symbol. */
    lv_draw_label_dsc_t label;
    init_label_dsc(&label, LVGL_FOREGROUND, &lv_font_montserrat_8, LV_TEXT_ALIGN_LEFT);
    char text[5];
    snprintf(text, sizeof(text), "%u%%", (unsigned int)battery);
    lv_canvas_draw_text(canvas, 25, 4, 26, &label, text);
}
