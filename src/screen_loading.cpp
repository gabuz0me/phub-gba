#include <bn_bgs_mosaic_actions.h>
#include <bn_core.h>
#include <bn_regular_bg_items_ph_main_page.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sound_handle.h>
#include <bn_sound_item.h>
#include <bn_sound_items.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "random_flat_curve.h"
#include "screen.h"

#include "bn_sprite_items_loading.h"

#include "common_fixed_8x16_sprite_font.h"

constexpr int frame_count_to_100 = 550; // Theoretical time to go to 100% loading
constexpr int percent_to_fail = 89;     // Trigger next screen after n %
constexpr int steps = 4;                // Flat steps in loading functions
constexpr int INT_MAX = 100;            // Everything is in percent now

class LoadingBar
{
  public:
    LoadingBar(bn::fixed_point position, int percent = 0)
        : _position(position),                                 //
          _spriteL(bn::sprite_items::loading.create_sprite()), //
          _spriteR(bn::sprite_items::loading.create_sprite())
    {
        set_percent(percent);
    }

    void set_percent(int percent)
    {
        percent = (15 * percent) / 100;
        _spriteL = bn::sprite_items::loading.create_sprite(_position.x() - 16, _position.y(), 2 * percent + 0);
        _spriteR = bn::sprite_items::loading.create_sprite(_position.x() + 16, _position.y(), 2 * percent + 1);
    }

  private:
    bn::fixed_point _position;
    bn::sprite_ptr _spriteL;
    bn::sprite_ptr _spriteR;
};

void show_screen_loading()
{
    constexpr bn::fixed_point loading_bar_pos(0, 60);
    constexpr bn::fixed_point loading_text_pos(0, loading_bar_pos.y() - 1);

    // BG
    bn::regular_bg_ptr bg = bn::regular_bg_items::ph_main_page.create_bg();
    bg.set_mosaic_enabled(true);

    // Loading Text
    bn::vector<bn::sprite_ptr, 3> loading_text_sprites;
    bn::sprite_text_generator generator(common::fixed_8x16_sprite_font);

    bn::array<bn::color, 16> colors;
    colors[0] = bn::colors::black;
    colors[1] = bn::colors::phub;
    colors[2] = bn::colors::black;
    bn::span<bn::color> color_span(colors);
    bn::sprite_palette_item palette(color_span, bn::bpp_mode::BPP_4);
    generator.set_palette_item(palette);
    generator.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);

    // Loading Bar
    LoadingBar loading_bar(loading_bar_pos);

    // Random curves
    const unsigned int old_seed = randomizer.seed();
    randomizer.set_seed(19);
    RandomFlatCurve<steps> curve_x(frame_count_to_100, INT_MAX);
    RandomFlatCurve<steps> curve_y(frame_count_to_100, INT_MAX);

    bn::sound_handle dial_up = bn::sound_items::dial_up.play();

    // Main Loop
    int current_frame = 0;
    while (current_frame < frame_count_to_100)
    {
        const int val_x = curve_x(current_frame);
        const int val_y = curve_y(current_frame);
        const int val_mean = (val_x + val_y) / 2;

        loading_bar.set_percent(val_mean);
        loading_text_sprites.clear();
        generator.generate(loading_text_pos, bn::to_string<3>(val_mean) + "%", loading_text_sprites);

        bn::fixed val;
        val = bn::fixed(INT_MAX - val_x) / INT_MAX;
        bn::bgs_mosaic::set_horizontal_stretch(val);

        val = bn::fixed(INT_MAX - val_y) / INT_MAX;
        bn::bgs_mosaic::set_vertical_stretch(val);

        ++current_frame;
        bn::core::update();
        if (val_mean > percent_to_fail)
            break;
    }

    if (dial_up.active())
        dial_up.stop();

    randomizer.set_seed(old_seed);
    current_screen = ScreenType::DELACROIX;
}