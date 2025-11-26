#include <bn_affine_bg_ptr.h>
#include <bn_blending.h>
#include <bn_core.h>
#include <bn_fixed_point_fwd.h>
#include <bn_keypad.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "screen.h"

// Images
#include "bn_affine_bg_items_logo.h"
#include "bn_algorithm.h"
#include "bn_fixed_fwd.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_delacroix.h"
#include "bn_regular_bg_items_ph_intro_1.h"
#include "bn_string_view.h"
#include "common.h"
#include "common_fixed_8x16_sprite_font.h"
#include "ti_font.h"

using namespace bn;

void show_screen_main(void)
{
    affine_bg_ptr bg = affine_bg_items::logo.create_bg(0, 0);

    sprite_text_generator txt_copyleft(common::fixed_8x16_sprite_font);
    vector<sprite_ptr, 13> txt_copyleft_sprite;
    txt_copyleft.generate(-120, 80 - 1 * 8, "Gabuzome", txt_copyleft_sprite);

    fixed_point txt_start_pos(0, 16 * 2);
    sprite_text_generator txt_start(common::fixed_8x16_sprite_font);
    vector<sprite_ptr, 13> txt_start_sprite;
    txt_start.set_alignment(sprite_text_generator::alignment_type::CENTER);
    txt_start.generate(txt_start_pos, "Press start !", txt_start_sprite);

    sprite_text_generator txt_version(common::fixed_8x16_sprite_font);
    vector<sprite_ptr, 13> txt_version_sprite;
    txt_version.set_alignment(sprite_text_generator::alignment_type::RIGHT);
    txt_version.generate(120, 80 - 1 * 8, "v0.0.0", txt_version_sprite);

    while (!(keypad::a_pressed() || keypad::start_pressed()))
    {
        core::update();
    }

    current_screen = ScreenType::DELACROIX;
    txt_start_sprite.clear();
    txt_start.generate(txt_start_pos, "Pressed \\o/", txt_start_sprite);
    core::update();
}

void show_screen_delacroix(void)
{
    constexpr bn::fixed scroll_y_max = +((256 / 2) - 80 - 27); // Scrolling delta for the top
    constexpr bn::fixed scroll_y_min = -((256 / 2) - 80 - 26); // Scrolling delta for the bottom
    bn::fixed scroll_y = scroll_y_max;
    bn::regular_bg_ptr bg = bn::regular_bg_items::delacroix.create_bg(0, scroll_y);
    bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0.5);

    // sprite_text_generator txt_test(ti::sips_font);
    sprite_text_generator txt_test(common::fixed_8x16_sprite_font);
    vector<sprite_ptr, 130> txt_test_sprite;
    constexpr bn::string_view txt("Ici le défilement.");
    txt_test.set_alignment(sprite_text_generator::alignment_type::CENTER);
    txt_test.generate(-0, 0, txt, txt_test_sprite);

    bn::fixed bg_scroll_speed = 1.7;
    while (true)
    {
        if (bn::keypad::down_held() && scroll_y > scroll_y_min)
        {
            scroll_y -= bg_scroll_speed;
            scroll_y = bn::max(scroll_y, scroll_y_min);
            bg.set_y(scroll_y);
        }
        if (bn::keypad::up_held() && scroll_y < scroll_y_max)
        {
            scroll_y += bg_scroll_speed;
            scroll_y = bn::min(scroll_y, scroll_y_max);
            bg.set_y(scroll_y);
        }
        bn::core::update();

        if (bn::keypad::a_pressed() || bn::keypad::start_pressed())
            break;
    }
    current_screen = ScreenType::ANIMATION;
}

void show_screen_intro(void)
{
    constexpr int frames_per_chunk = 45;
    constexpr int total_frames = 45;
    constexpr int frame_interval = 2; // 30 FPS
    int frame = 0;
    int counter = 0;
    bn::regular_bg_ptr bg = bn::regular_bg_items::ph_intro_1.create_bg();
    bg.set_top_left_position(0, 0);

    while (true)
    {
        if (++counter >= frame_interval)
        {
            counter = 0;
            frame = (frame + 1) % total_frames;

            int frame_in_chunk = frame % frames_per_chunk;

            int x_offset = -frame_in_chunk * 240;

            bg.set_top_left_position(x_offset, 0);
        }

        bn::core::update();
    }
}