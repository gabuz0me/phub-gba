#include <bn_core.h>
#include <bn_fixed_point_fwd.h>
#include <bn_optional.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sound_items.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

// Project
#include "screen.h"
#include "utils.h"

// Images
#include "bn_regular_bg_items_delacroix.h"
#include "bn_sprite_items_button_a.h"
#include "bn_sprite_items_exit.h"

// Fonts
#include "common_fixed_8x16_sprite_font.h"
#include "common_fixed_8x8_sprite_font.h"
#include "common_variable_8x16_sprite_font.h"
#include "common_variable_8x8_sprite_font.h"

#include "verdana9_bold_8x16_sprite_font.h"
#include "verdana9_normal_8x16_sprite_font.h"

// This header defines `displayed_text` and `text_width`
#include "text/text_delacroix_fr_verdana9_normal_8x16_sprite_font.h"

// Customization!
constexpr int line_height = 12;
constexpr int nb_lines_seen = 8;

// Shenanigans
constexpr int text_y_coord_base = ((nb_lines_seen + 1) * line_height) / 2;
constexpr int text_x_coord_base = -text_width / 2;
constexpr int nb_lines = sizeof(displayed_text) / sizeof(displayed_text[0]);
constexpr int max_camera_position = line_height * (nb_lines - nb_lines_seen);
typedef bn::vector<bn::sprite_ptr, 64> SpriteLine;
typedef bn::vector<SpriteLine, nb_lines_seen + 1> SpriteLineList;

void refresh_screen_text(bn::sprite_text_generator &generator, //
                         SpriteLineList &sprite_line_list,     //
                         int &current_top_line,                //
                         bn::fixed camera_y)
{
    int top = bn::clamp(int(camera_y / line_height), 0, nb_lines - 1);
    if (top == current_top_line)
        return;
    current_top_line = top;
    for (int visible_line_index = 0; visible_line_index <= nb_lines_seen; ++visible_line_index)
    {
        SpriteLine line;
        generator.generate(text_x_coord_base,
                           text_y_coord_base + line_height * (current_top_line + visible_line_index - nb_lines_seen),
                           displayed_text[current_top_line + visible_line_index], line);
        sprite_line_list[visible_line_index] = bn::move(line);
    }
}

constexpr int frame_fading = 30;

constexpr bn::fixed_point pos_button_a(-8, 80 - 16);
constexpr bn::fixed_point pos_exit(8, 80 - 16);

void show_screen_delacroix(void)
{
    constexpr int bg_scroll_y_max = +((256 / 2) - 80 - 21); // Scrolling delta for the top
    constexpr int bg_scroll_y_min = -((256 / 2) - 80 - 21); // Scrolling delta for the bottom
    constexpr bn::fixed scroll_speed = 2.5;

    bn::fixed bg_scroll_y = bg_scroll_y_max;
    bn::regular_bg_ptr bg = bn::regular_bg_items::delacroix.create_bg(0, bg_scroll_y);
    bg.set_blending_enabled(true);
    int current_top_line = -1;

    bn::sprite_text_generator generator(verdana9::normal_8x16_sprite_font);
    generator.set_blending_enabled(true);
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    generator.set_camera(camera);
    SpriteLineList sprite_lines_list(nb_lines_seen + 1, SpriteLine());
    refresh_screen_text(generator, sprite_lines_list, current_top_line, camera.y());

    // Buttons?
    bn::optional<bn::sprite_ptr> button_a;
    bn::optional<bn::sprite_ptr> exit;

    // Sound
    bn::optional<bn::sound_handle> handle_trololo;
    bn::sound_handle handle_error = bn::sound_items::windows_error.play();
    constexpr int frame_before_playing = 300;
    int frame = 0;
    while (true)
    {
        if (frame >= frame_before_playing && (!handle_trololo.has_value() || !handle_trololo->active()))
            handle_trololo = bn::sound_items::trololo_deg.play(0.7);

        bn::fixed dy = (int(bn::keypad::down_held()) - int(bn::keypad::up_held())) * scroll_speed;
        camera.set_y(bn::clamp<bn::fixed>(camera.y() + dy, 0, max_camera_position));

        const bn::fixed bg_y = bg_scroll_y_max + camera.y() * bg_scroll_y_min / max_camera_position;
        bg.set_y(bg_y);

        refresh_screen_text(generator, sprite_lines_list, current_top_line, camera.y());

        if (!button_a && camera.y() > max_camera_position - line_height * 3)
        {
            button_a = bn::sprite_items::button_a.create_sprite(pos_button_a, 0);
            exit = bn::sprite_items::exit.create_sprite(pos_exit);
        }

        bn::core::update();
        if (button_a && a_or_start_pressed())
        {
            button_a = bn::sprite_items::button_a.create_sprite(pos_button_a, 1);
            break;
        }
        ++frame;
    }

    button_a->set_blending_enabled(true);
    exit->set_blending_enabled(true);
    fade(Fade::OUT, frame_fading);
    if (handle_error.active())
        handle_error.stop();
    if (handle_trololo && handle_trololo->active())
        handle_trololo->stop();

    current_screen = ScreenType::OTHER_GAMES;
}
