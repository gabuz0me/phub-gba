#include <bn_blending.h>
#include <bn_colors.h>
#include <bn_core.h>
#include <bn_log.h>
#include <bn_string.h>

#include "bn_color.h"
#include "utils.h"

bn::sprite_palette_item simple_text_palette(bn::color color_main, bn::color color_other)
{
    bn::array<bn::color, 16> colors;
    colors[0] = bn::colors::black;
    colors[1] = color_main;
    colors[2] = color_other;
    bn::span<bn::color> color_span(colors);
    return bn::sprite_palette_item(color_span, bn::bpp_mode::BPP_4);
}

void fade(Fade fade, int frame_count, bn::optional<bn::blending::fade_color_type> color)
{
    if (color)
        bn::blending::set_fade_color(color.value());

    int frame = frame_count + 1;
    while (--frame)
    {
        auto val = bn::fixed(frame) / frame_count;
        if (fade == Fade::OUT)
            val = 1. - val;
        bn::blending::set_fade_alpha(val);
        bn::core::update();
    }
    bn::blending::set_fade_alpha(0);
}