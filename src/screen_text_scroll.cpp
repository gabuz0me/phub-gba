#include <bn_blending.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_string.h>

#include <bn_log.h>

// Project
#include "screen.h"

// Images
#include "bn_regular_bg_items_delacroix.h"

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

void show_screen_delacroix(void)
{
    constexpr int bg_scroll_y_max = +((256 / 2) - 80 - 27); // Scrolling delta for the top
    constexpr int bg_scroll_y_min = -((256 / 2) - 80 - 26); // Scrolling delta for the bottom
    constexpr bn::fixed scroll_speed = 2.5;

    bn::fixed bg_scroll_y = bg_scroll_y_max;
    bn::regular_bg_ptr bg = bn::regular_bg_items::delacroix.create_bg(0, bg_scroll_y);
    bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0.5);

    int current_top_line = -1;

    bn::sprite_text_generator generator(verdana9::normal_8x16_sprite_font);
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    generator.set_camera(camera);
    SpriteLineList sprite_lines_list(nb_lines_seen + 1, SpriteLine());

    while (true)
    {
        bn::fixed dy = (int(bn::keypad::down_held()) - int(bn::keypad::up_held())) * scroll_speed;
        camera.set_y(bn::clamp<bn::fixed>(camera.y() + dy, 0, max_camera_position));

        const bn::fixed bg_y = bg_scroll_y_max + camera.y() * bg_scroll_y_min / max_camera_position;
        bg.set_y(bg_y);

        refresh_screen_text(generator, sprite_lines_list, current_top_line, camera.y());

        bn::core::update();
        if (a_or_start_pressed())
            break;
    }
    current_screen = ScreenType::OTHER_GAMES;
}
