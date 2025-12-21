#include "screen.h"
#ifdef SPLASH_SCREEN
// ========================================================================== //

#include <bn_bgs_mosaic.h>
#include <bn_blending.h>
#include <bn_core.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sound_items.h>

#include "bn_regular_bg_items_splash_screen.h"

#include "utils.h"

constexpr int frame_fade_in = 60;
constexpr int frame_hold = 120;
constexpr int frame_fade_out = 60;

void show_screen_splash()
{
    bn::blending::set_white_fade_color();
    bn::regular_bg_ptr bg = bn::regular_bg_items::splash_screen.create_bg();
    bg.set_mosaic_enabled(true);
    bg.set_blending_enabled(true);

    // Fade In
    int frame;
    frame = frame_fade_in + 1;
    while (--frame)
    {
        const bn::fixed ratio = bn::fixed(frame) / frame_fade_in;
        bn::blending::set_fade_alpha(ratio);
        bn::bgs_mosaic::set_stretch(ratio);
        bn::core::update();
    }

    bn::sound_items::kazoo_tada.play(0.7);

    // Hold
    frame = frame_hold + 1;
    while (--frame)
    {
        bn::core::update();
    }

    // Fade Out
    bn::blending::set_black_fade_color();
    frame = frame_fade_out + 1;
    while (--frame)
    {
        const bn::fixed ratio = 1. - bn::fixed(frame) / frame_fade_out;
        bn::blending::set_fade_alpha(ratio);
        bn::bgs_mosaic::set_stretch(ratio);
        bn::core::update();
    }

    bn::blending::set_fade_alpha(0);
    current_screen = ScreenType::TITLE;
}

// ========================================================================== //
#endif