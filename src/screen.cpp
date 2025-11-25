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
    bn::blending::set_transparency_alpha(0.2);

    sprite_text_generator txt_test(ti::sips_font);
    // sprite_text_generator txt_test(common::fixed_8x16_sprite_font);
    vector<sprite_ptr, 130> txt_test_sprite;
    constexpr bn::string_view txt("Trés le test: áéíóúüñ¡¿αβ");
    txt_test.generate(-120, 80 - 1 * 8, txt, txt_test_sprite);

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
    }
}