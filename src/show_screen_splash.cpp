#include "screen.h"
#ifdef SPLASH_SCREEN
// ========================================================================== //

#include <bn_bg_palettes.h>
#include <bn_bgs_mosaic.h>
#include <bn_blending.h>
#include <bn_colors.h>
#include <bn_core.h>
#include <bn_regular_bg_ptr.h>

#include "bn_regular_bg_items_splash_screen.h"

constexpr int frame_fade_in = 60;
constexpr int frame_hold = 120;
constexpr int frame_fade_out = 60;

void show_screen_splash()
{
    int frame;
    bn::bg_palettes::set_transparent_color(bn::colors::white);
    bn::regular_bg_ptr bg = bn::regular_bg_items::splash_screen.create_bg();
    bg.set_mosaic_enabled(true);
    bg.set_blending_enabled(true);

    // Fade In
    frame = frame_fade_in + 1;
    while (--frame)
    {
        const bn::fixed ratio = bn::fixed(frame) / frame_fade_in;
        bn::blending::set_transparency_alpha(1. - ratio);
        bn::bgs_mosaic::set_stretch(ratio);
        bn::core::update();
    }

    // Hold
    frame = frame_hold + 1;
    while (--frame)
    {
        bn::core::update();
    }

    // Fade Out
    bn::bg_palettes::set_transparent_color(bn::colors::black);
    frame = frame_fade_out + 1;
    while (--frame)
    {
        const bn::fixed ratio = bn::fixed(frame) / frame_fade_out;
        bn::blending::set_transparency_alpha(ratio);
        bn::bgs_mosaic::set_stretch(1. - ratio);
        bn::core::update();
    }

    current_screen = ScreenType::TITLE;
}

// ========================================================================== //
#endif