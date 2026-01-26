#include <bn_bg_palette_ptr.h>
#include <bn_bg_palettes.h>
#include <bn_core.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sound_handle.h>
#include <bn_sound_items.h>
#include <bn_sprite_items_button_center_side.h>
#include <bn_sprite_text_generator.h>

#include "verdana9_bold_8x16_sprite_font.h"
#include "verdana9_italic_8x16_sprite_font.h"
#include "verdana9_normal_8x16_sprite_font.h"

#include "bn_regular_bg_items_showcase.h"

#include "bn_sprite_items_button_a.h"
#include "bn_sprite_items_button_b.h"
#include "bn_sprite_items_exit.h"
#include "bn_sprite_items_shuffle.h"

#include "multi_sprite.h"
#include "screen.h"
#include "utils.h"

constexpr int radius_min = 3;
constexpr int radius_max = 5;
constexpr int random_frame_min = 60 * 3;
constexpr int random_frame_max = 60 * 5;

// creates `all_cartridges` and `all_cartridge_size`
#include "cartridges.h"

typedef bn::vector<int, all_cartridge_size> int_list;

class Cartridge : MultiSprite
{
  public:
    Cartridge(bn::sprite_item item, bn::fixed x = 0, bn::fixed y = 0) : Cartridge(item, bn::fixed_point(x, y)) {}
    Cartridge(bn::sprite_item item, const bn::fixed_point &position)
        : MultiSprite(item, position), _original_pos(position)
    {
        create_target();
        set_blending_enabled(true);
    }

    void create_target()
    {
        int radius = randomizer.get_int(radius_min, radius_max);
        _delta_xy = bn::fixed_point(randomizer.get_fixed(-radius, radius), randomizer.get_fixed(-radius, radius));
        // _phase_xy = bn::fixed_point(randomizer.get_fixed(radius), randomizer.get_fixed(radius));
        _current_tick = 0;
        _target_tick = randomizer.get_int(random_frame_min, random_frame_max);
    }

    void update()
    {
        if (_current_tick >= _target_tick)
        {
            create_target();
            return;
        }
        bn::fixed theta = _current_tick / _target_tick;
        theta = smoothstep(theta);
        bn::fixed _x = _original_pos.x() + bn::sin(theta) * _delta_xy.x();
        bn::fixed _y = _original_pos.y() + bn::sin(theta) * _delta_xy.y();
        set_position(_x, _y);
        _current_tick += 1;
    }

    enum class Status : int
    {
        NORMAL,
        FADE_OUT,
        FADE_IN
    };

  private:
    bn::fixed_point _original_pos;
    bn::fixed _current_tick = 0;
    bn::fixed _target_tick;
    bn::fixed_point _delta_xy;
};

constexpr bn::fixed x_delta(50);
constexpr bn::fixed y_text(-60);
constexpr bn::fixed y_bot_delta(35);
constexpr bn::fixed y_top_delta(-25);

bn::vector<Cartridge, 4> cartridges;

void update_cartridges(const int_list &random_index_list)
{
    static int count = 0;
    cartridges.clear();
    for (int i = 0; i < 4; ++i)
    {
        const int index = random_index_list[(count * 4 + i) % all_cartridge_size];
        const bn::fixed &x = i % 2 ? -x_delta : x_delta;
        const bn::fixed &y = i < 2 ? y_top_delta : y_bot_delta;
        cartridges.push_back(Cartridge(all_cartridges[index], x, y));
    }
    count += 1;
}

constexpr bn::fixed_point button_b_pos(-120 + 8, 80 - 8);
constexpr bn::fixed_point button_a_pos(120 - 8, 80 - 8);

void update_status(Cartridge::Status &status, const int_list &random_index_list, bn::sprite_ptr &button_b)
{
    constexpr int frame_fade_duration = 10;
    static int frame_fade = frame_fade_duration + 1;
    if (bn::keypad::b_pressed() && status == Cartridge::Status::NORMAL)
    {
        status = Cartridge::Status::FADE_OUT;
        button_b = bn::sprite_items::button_b.create_sprite(button_b_pos, 1);
        bn::sound_items::woosh.play();
    }
    else if (status == Cartridge::Status::FADE_OUT)
    {
        if (--frame_fade)
        {
            bn::blending::set_transparency_alpha(bn::fixed(frame_fade) / frame_fade_duration);
        }
        else
        {
            frame_fade = frame_fade_duration + 1;
            update_cartridges(random_index_list);
            status = Cartridge::Status::FADE_IN;
        }
    }
    else if (status == Cartridge::Status::FADE_IN)
    {
        if (--frame_fade)
        {
            bn::blending::set_transparency_alpha(1. - bn::fixed(frame_fade) / frame_fade_duration);
        }
        else
        {
            frame_fade = frame_fade_duration + 1;
            status = Cartridge::Status::NORMAL;
            button_b = bn::sprite_items::button_b.create_sprite(button_b_pos, 0);
            bn::blending::set_transparency_alpha(1);
        }
    }
}

constexpr bn::fixed volume_music(0.5);
void show_screen_other_games(void)
{
    bn::sound_handle music = bn::sound_items::relaxation.play(volume_music);

    bn::regular_bg_ptr bg = bn::regular_bg_items::showcase.create_bg(0, 0);
    bn::bg_palettes::set_transparent_color(bg.palette().colors()[0]);

    bn::sprite_text_generator generator(verdana9::bold_8x16_sprite_font);
    bn::array<bn::color, 16> colors;
    colors[0] = bn::colors::black;
    colors[1] = bn::colors::black;
    bn::span<bn::color> color_span(colors);
    bn::sprite_palette_item palette(color_span, bn::bpp_mode::BPP_4);
    generator.set_palette_item(palette);
    bn::vector<bn::sprite_ptr, 40> sprites;
    generator.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    generator.generate(0, y_text, "Découvrez tous nos autres jeux !", sprites);

    int_list random_index_list;
    generate_random_order(random_index_list);
    update_cartridges(random_index_list);

    auto button_b = bn::sprite_items::button_b.create_sprite(button_b_pos);
    auto shuffle = bn::sprite_items::shuffle.create_sprite(button_b_pos + bn::fixed_point(16, 0));
    auto exit = bn::sprite_items::exit.create_sprite(120 - 8 - 16, 80 - 8);
    auto button_a = bn::sprite_items::button_a.create_sprite(120 - 8, 80 - 8);

    auto status = Cartridge::Status::NORMAL;
    while (true)
    {
        if (!music.active())
            music = bn::sound_items::relaxation.play(volume_music);

        if (a_or_start_pressed() && status == Cartridge::Status::NORMAL)
        {
            button_a = bn::sprite_items::button_a.create_sprite(button_a_pos, 1);
            break;
        }
        for (auto &cartridge : cartridges) // Comment this to disable cartridge movement
            cartridge.update();
        update_status(status, random_index_list, button_b);
        bn::core::update();
    }

    button_b.set_blending_enabled(true);
    shuffle.set_blending_enabled(true);
    button_a.set_blending_enabled(true);
    exit.set_blending_enabled(true);
    bg.set_blending_enabled(true);
    fade(Fade::OUT, 90);
    cartridges.clear();
    if (music.active())
        music.stop();
    current_screen = ScreenType::TITLE;
}
