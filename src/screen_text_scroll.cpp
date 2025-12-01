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

constexpr int nb_lines = 27;
typedef bn::vector<bn::sprite_ptr, 64> SpriteLine;
typedef bn::vector<SpriteLine, nb_lines> SpriteLineList;

constexpr int max_line_sprite_count = 64;
constexpr int line_height = 14;
constexpr int line_seen_count = 3;
constexpr int max_camera_position = line_height * (nb_lines - line_seen_count);

bn::string<max_line_sprite_count> lorem[27] = {"Lorem ipsum dolor sit amet consectetur adipiscing elit. Semper",
                                               "vel class aptent taciti sociosqu ad litora. Blandit quis",
                                               "suspendisse aliquet nisi sodales consequat magna. Cras eleifend",
                                               "turpis fames primis vulputate ornare sagittis. Sem placerat in",
                                               "id cursus mi pretium tellus. Orci varius natoque penatibus et",
                                               "magnis dis parturient. Finibus facilisis dapibus etiam interdum",
                                               "tortor ligula congue. Proin libero feugiat tristique accumsan",
                                               "maecenas potenti ultricies. Sed diam urna tempor pulvinar",
                                               "vivamus fringilla lacus. Eros lobortis nulla molestie mattis",
                                               "scelerisque maximus eget. Porta elementum a enim euismod quam",
                                               "justo lectus. Curabitur facilisi cubilia curae hac habitase",
                                               "platea dictumst. Nisl malesuada lacinia integer nunc posuere ut",
                                               "hendrerit. Efficitur laoreet mauris pharetra vestibulum fusce",
                                               "dictum risus. Imperdiet mollis nullam volutpat porttitor",
                                               "ullamcorper rutrum gravida. Adipiscing elit quisque faucibus ex",
                                               "sapien vitae pellentesque. Ad litora torquent per conubia nostra",
                                               "inceptos himenaeos. Consequat magna ante condimentum neque at",
                                               "luctus nibh. Ornare sagittis vehicula praesent dui felis",
                                               "venenatis ultrices. Pretium tellus duis convallis tempus leo eu",
                                               "aenean. Dis parturient montes nascetur ridiculus mus donec",
                                               "rhoncus. Ligula congue sollicitudin erat viverra ac tincidunt",
                                               "nam. Potenti ultricies habitant morbi senectus netus suscipit",
                                               "auctor. Fringilla lacus nec metus bibendum egestas iaculis",
                                               "massa. Maximus eget fermentum odio phasellus non purus est.",
                                               "Justo lectus commodo augue arcu dignissim velit aliquam. Platea",
                                               "dictumst lorem ipsum dolor sit amet consectetur. Ut hendrerit",
                                               "semper vel class aptent taciti sociosqu. Dictum risus blandit."};

void refresh_screen_text(bn::sprite_text_generator &generator, //
                         SpriteLineList &sprite_line_list,     //
                         int &current_top_line,                //
                         bn::fixed camera_y)
{
    int top = bn::clamp(int(camera_y / line_height), 0, nb_lines - 1);
    // int top = bn::clamp(int(camera_y / line_height), -line_seen_count, nb_lines - 1 + line_seen_count);
    if (top == current_top_line)
        return;
    current_top_line = top;
    const int current_bottom_line = current_top_line + line_seen_count;

    bn::log(bn::to_string<20>(top) + " -> " + bn::to_string<20>(current_bottom_line));
    for (int line_index = 0; line_index < nb_lines; ++line_index)
    {
        auto &sprite_line = sprite_line_list[line_index];
        if (current_top_line <= line_index && line_index <= current_bottom_line)
        {
            if (sprite_line.empty())
            {
                SpriteLine line;
                generator.generate_top_left(0, 160 - line_height * line_seen_count + line_index * line_height - 3,
                                            lorem[line_index], line);
                sprite_line_list[line_index] = bn::move(line);
            }
        }
        else
        {
            if (!sprite_line.empty())
                sprite_line.clear();
        }
    }
}

void show_screen_delacroix(void)
{
    constexpr bn::fixed scroll_y_max = +((256 / 2) - 80 - 27); // Scrolling delta for the top
    constexpr bn::fixed scroll_y_min = -((256 / 2) - 80 - 26); // Scrolling delta for the bottom
    constexpr bn::fixed bg_speed = bn::fixed(27 + 26) / (line_height * nb_lines);

    bn::fixed scroll_y = scroll_y_max;
    bn::regular_bg_ptr bg = bn::regular_bg_items::delacroix.create_bg(0, scroll_y);
    bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0.5);

    int current_top_line = -1;
    bn::sprite_text_generator generator(verdana9::normal_8x16_sprite_font);
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    generator.set_camera(camera);
    SpriteLineList sprite_lines_list(nb_lines, SpriteLine());

    while (true)
    {
        int dy = int(bn::keypad::down_held()) - int(bn::keypad::up_held());
        camera.set_y(bn::clamp(int(camera.y() + dy), 0, max_camera_position));
        bg.set_y(bn::clamp(bg.y() - dy * bg_speed, scroll_y_min, scroll_y_max));
        refresh_screen_text(generator, sprite_lines_list, current_top_line, camera.y());
        bn::core::update();
        if (a_or_start_pressed())
            break;
    }
    current_screen = ScreenType::OTHER_GAMES;
}
