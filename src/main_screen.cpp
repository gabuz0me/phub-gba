#include <bn_affine_bg_ptr.h>
#include <bn_core.h>
#include <bn_keypad.h>
// #include <bn_log.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "main_screen.h"

// Images
#include "bn_affine_bg_items_logo.h"
#include "bn_fixed_point_fwd.h"
#include "common.h"
#include "common_fixed_8x16_sprite_font.h"

using namespace bn;

void show_main_screen(void)
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

    screen_type = ScreenType::LOADING;
    txt_start_sprite.clear();
    txt_start.generate(txt_start_pos, "Pressed \\o/", txt_start_sprite);
    core::update();
    while (true)
        ;
}