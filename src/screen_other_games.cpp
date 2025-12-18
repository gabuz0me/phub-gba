#include <bn_bg_palette_ptr.h>
#include <bn_bg_palettes.h>
#include <bn_colors.h>
#include <bn_core.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_sprite_tiles_ptr.h>

#include "verdana9_bold_8x16_sprite_font.h"
#include "verdana9_italic_8x16_sprite_font.h"
#include "verdana9_normal_8x16_sprite_font.h"

#include "bn_regular_bg_items_showcase.h"

#include "bn_sprite_items_arte.h"
#include "bn_sprite_items_canal.h"
#include "bn_sprite_items_francetv.h"
#include "bn_sprite_items_netflix.h"
#include "bn_sprite_items_ph.h"
#include "bn_sprite_items_youtube.h"

#include "multi_sprite.h"
#include "screen.h"
#include "utils.h"

constexpr int radius_min = 3;
constexpr int radius_max = 5;
constexpr int random_frame_min = 60 * 3;
constexpr int random_frame_max = 60 * 5;

constexpr int all_cartridge_size = 6;
bn::sprite_item all_cartridges[] = {
    bn::sprite_items::arte,     //
    bn::sprite_items::canal,    //
    bn::sprite_items::francetv, //
    bn::sprite_items::netflix,  //
    bn::sprite_items::ph,       //
    bn::sprite_items::youtube,  //
};

#include <bn_log.h>
#include <bn_string.h>
class Cartridge : MultiSprite
{
  public:
    Cartridge(bn::sprite_item item, bn::fixed x = 0, bn::fixed y = 0) : Cartridge(item, bn::fixed_point(x, y)) {}
    Cartridge(bn::sprite_item item, const bn::fixed_point &position)
        : MultiSprite(item, position), _original_pos(position)
    {
        create_target();
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

  private:
    bn::fixed_point _original_pos;
    bn::fixed _current_tick = 0;
    bn::fixed _target_tick;
    bn::fixed_point _delta_xy;
};

constexpr bn::fixed x_delta(50);
constexpr bn::fixed y_bot_delta(50);
constexpr bn::fixed y_top_delta(-10);

void show_screen_other_games(void)
{
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
    generator.generate(0, -50, "Découvrez tous nos autres jeux !", sprites);

    bn::vector<int, all_cartridge_size> random_index;
    generate_random_order(random_index);

    Cartridge cartridges[4] = {
        Cartridge(all_cartridges[random_index[0]], -x_delta, y_bot_delta),
        Cartridge(all_cartridges[random_index[1]], x_delta, y_top_delta),
        Cartridge(all_cartridges[random_index[2]], -x_delta, y_top_delta),
        Cartridge(all_cartridges[random_index[3]], x_delta, y_bot_delta),
    };

    bn::core::update();
    while (true)
    {
        if (a_or_start_pressed())
            break;
        for (auto &cartridge : cartridges)
            cartridge.update();
        bn::core::update();
    }

    current_screen = ScreenType::VERIFICATION;
}
