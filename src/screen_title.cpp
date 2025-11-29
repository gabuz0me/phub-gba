#include <bn_affine_bg_ptr.h>
#include <bn_core.h>
#include <bn_sound_items.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

// Project
#include "screen.h"

// Images
#include "bn_affine_bg_items_logo.h"

// Fonts
#include "common_fixed_8x16_sprite_font.h"
#include "common_fixed_8x8_sprite_font.h"
#include "common_variable_8x16_sprite_font.h"
#include "common_variable_8x8_sprite_font.h"

#include "verdana9_bold_8x16_sprite_font.h"
#include "verdana9_italic_8x16_sprite_font.h"
#include "verdana9_normal_8x16_sprite_font.h"

constexpr bn::fixed_point txt_start_pos(0, 16 * 2);

void toggle_start_text(bn::sprite_text_generator &generator, bn::vector<bn::sprite_ptr, 32> &sprites, bool visible)
{
    if (visible)
        generator.generate(txt_start_pos, "Press start!", sprites);
    else
        sprites.clear();
}

constexpr int y_bottom = 80 - 4;

void show_screen_main(void)
{
    bn::core::update();
    bn::affine_bg_ptr bg = bn::affine_bg_items::logo.create_bg(0, 0);

    bn::sprite_text_generator txt_copyleft(verdana9::normal_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 32> txt_copyleft_sprite;
    txt_copyleft.generate(-120 + 3, y_bottom, "⋅   Gabuzome 2025", txt_copyleft_sprite);

    bn::sprite_text_generator txt_start(verdana9::bold_8x16_sprite_font);
    txt_start.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    bn::vector<bn::sprite_ptr, 32> txt_start_sprite;
    bool txt_start_visible = true;
    toggle_start_text(txt_start, txt_start_sprite, txt_start_visible);

    bn::sprite_text_generator txt_version(verdana9::italic_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 32> txt_version_sprite;
    txt_version.set_alignment(bn::sprite_text_generator::alignment_type::RIGHT);
    txt_version.generate(120 - 3, y_bottom, "v0.69", txt_version_sprite);

    bn::sound_handle handle_intro = bn::sound_items::yello_oh_yeah_intro.play();
    bn::optional<bn::sound_handle> handle_loop;
    bool sound_loop = false;

    int frame_count = 0;
    while (!a_or_start_pressed())
    {
        if (++frame_count == 30)
        {
            frame_count = 0;
            txt_start_visible = !txt_start_visible;
            toggle_start_text(txt_start, txt_start_sprite, txt_start_visible);
        }

        if (!sound_loop && !handle_intro.active())
            sound_loop = true;
        if (sound_loop && (!handle_loop || !handle_loop->active()))
            handle_loop = bn::sound_items::yello_oh_yeah_loop.play();

        bn::core::update();
    }

    if (handle_intro.active())
        handle_intro.stop();
    if (handle_loop && handle_loop->active())
        handle_loop->stop();

    current_screen = ScreenType::PH_INTRO;
}
