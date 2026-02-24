#include <bn_affine_bg_ptr.h>
#include <bn_bg_palettes.h>
#include <bn_core.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sound_items.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_timer.h>

// Project
#include "screen.h"
#include "utils.h"

// Images
#include "bn_affine_bg_items_title_bg.h"
#include "bn_regular_bg_items_title_logo.h"

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
    bn::bg_palettes::set_transparent_color(bn::colors::black);
    bn::affine_bg_ptr bg = bn::affine_bg_items::title_bg.create_bg(0, 0);
    bg.set_scale(0.5);
    bg.set_blending_enabled(true);

    bn::regular_bg_ptr main_logo = bn::regular_bg_items::title_logo.create_bg(0, 0);
    main_logo.set_blending_enabled(true);

    // Texts
    bn::sprite_text_generator txt_copyleft(verdana9::normal_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 32> txt_copyleft_sprite;
    txt_copyleft.generate(-120 + 3, y_bottom, "⋅  Gabuzome 2026", txt_copyleft_sprite);
    txt_copyleft.set_blending_enabled(true);

    bn::sprite_text_generator txt_start(verdana9::bold_8x16_sprite_font);
    txt_start.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    bn::vector<bn::sprite_ptr, 32> txt_start_sprite;
    bool txt_start_visible = true;
    toggle_start_text(txt_start, txt_start_sprite, txt_start_visible);
    txt_start.set_blending_enabled(true);

    bn::sprite_text_generator txt_version(verdana9::italic_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 32> txt_version_sprite;
    txt_version.set_alignment(bn::sprite_text_generator::alignment_type::RIGHT);
    txt_version.generate(120 - 3, y_bottom, "v0.69", txt_version_sprite);
    txt_version.set_blending_enabled(true);

    // Sound
    bn::sound_handle handle_intro = bn::sound_items::yello_oh_yeah_intro.play();
    bn::optional<bn::sound_handle> handle_loop;
    bool sound_loop = false;

    // Main Loop
    bn::timer timer;
    int ticks = 0;
    int frame_count = 0;

    constexpr int frame_fade_time = 15;
    int frame_fade_count = frame_fade_time + 1;
    bool pressed = false;
    while (true)
    {
        bg.set_position(bg.position() + bn::fixed_point(0.25, 0.5));

        if (a_or_start_pressed() || pressed)
        {
            pressed = true;
            if (!--frame_fade_count)
                break;
            bn::blending::set_fade_alpha(1. - bn::fixed(frame_fade_count) / frame_fade_time);
        }

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

        ticks += timer.elapsed_ticks_with_restart();
        bn::core::update();
    }

    if (handle_intro.active())
        handle_intro.stop();
    if (handle_loop && handle_loop->active())
        handle_loop->stop();

    bn::blending::set_fade_alpha(0);
    randomizer.set_seed(ticks);
    current_screen = ScreenType::PH_INTRO;
}
