#include <bn_audio.h>
#include <bn_bg_palettes.h>
#include <bn_colors.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sound_items.h>
// Project
#include "screen.h"

// Images
#include "bn_regular_bg_items_ph_intro_1.h"
#include "bn_regular_bg_items_ph_intro_2.h"
#include "bn_regular_bg_items_ph_intro_3.h"

void show_screen_animation(void)
{
    bn::bg_palettes::set_transparent_color(bn::colors::black);

    constexpr int frames_per_chunk[3] = {45, 23, 22};
    constexpr int frame_interval = 2; // 60/2=30 FPS
    constexpr bn::regular_bg_item bgs[3] = {
        bn::regular_bg_items::ph_intro_1, //
        bn::regular_bg_items::ph_intro_2, //
        bn::regular_bg_items::ph_intro_3, //
    };

    int frame = 0;
    int counter = 0;
    int current_chunk = 0;
    bn::regular_bg_ptr bg = bgs[0].create_bg();
    bg.set_top_left_position(0, 0);

    bn::core::update();
    bn::sound_items::ph_intro.play();
    while (true)
    {
        if (++counter >= frame_interval)
        {
            counter = 0;
            if (++frame >= frames_per_chunk[current_chunk])
            {
                frame = 0;
                current_chunk = (current_chunk + 1) % 3;
                if (current_chunk == 0)
                    break;
                bg.set_item(bgs[current_chunk]);
            }
            bg.set_top_left_position(-frame * 240, 0);
        }
        bn::core::update();
    }

    while (frame < 60 * 1) // wait 2 seconds
    {
        ++frame;
        bn::core::update();
    }
    current_screen = ScreenType::TITLE;
}