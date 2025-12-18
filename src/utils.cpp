#include "utils.h"

#include <bn_colors.h>
#include <bn_log.h>
#include <bn_string.h>

bn::sprite_palette_item simple_text_palette(bn::color color_main, bn::color color_other)
{
    bn::array<bn::color, 16> colors;
    colors[0] = bn::colors::black;
    colors[1] = color_main;
    colors[2] = color_other;
    bn::span<bn::color> color_span(colors);
    return bn::sprite_palette_item(color_span, bn::bpp_mode::BPP_4);
}