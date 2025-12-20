#include <bn_bg_palettes.h>
#include <bn_core.h>
#include <bn_sprite_text_generator.h>

#include "verdana9_bold_8x16_sprite_font.h"
#include "verdana9_italic_8x16_sprite_font.h"
#include "verdana9_normal_8x16_sprite_font.h"

#include "multi_sprite.h"
#include "screen.h"
#include "utils.h"

#include "bn_sprite_items_button_center_side.h"
#include "bn_sprite_items_button_circle_left.h"
#include "bn_sprite_items_button_dither.h"
#include "bn_sprite_items_button_progress.h"
#include "bn_sprite_items_button_radial_swipe.h"

#include "bn_sprite_items_ph_pixel_small.h"

#include "text/text_verification_fr_verdana9_italic_8x16_sprite_font.h"
// #include "text/text_verification_en_verdana9_italic_8x16_sprite_font.h"
constexpr int nb_lines = sizeof(displayed_text) / sizeof(displayed_text[0]);

// constexpr char top_text[] = "This is an adult website";
constexpr char top_text[] = "Ceci est un site web destiné aux adultes!";

constexpr bn::sprite_item button_sprites[] = {
    bn::sprite_items::button_center_side,  //
    bn::sprite_items::button_circle_left,  //
    bn::sprite_items::button_dither,       //
    bn::sprite_items::button_progress,     //
    bn::sprite_items::button_radial_swipe, //
};
constexpr int nb_button_sprites = sizeof(button_sprites) / sizeof(button_sprites[0]);

class Button
{
  public:
    Button(const bn::sprite_item &sprite_item, const bn::fixed_point &position, bool selected, bn::string_view txt)
        : _sprite(sprite_item), _sL(sprite_item.create_sprite(0)), _sR(sprite_item.create_sprite(1)),
          _generator(verdana9::normal_8x16_sprite_font)
    {
        set_position(position);
        _selected = !selected; // force graphic update
        set_selected(selected);

        _generator.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
        _generator.set_blending_enabled(true);
        _generator.generate(position.x(), position.y() + 1, txt, _text);
        for (bn::sprite_ptr &sprite : _text)
            sprite.set_z_order(0);
    }

    void set_position(const bn::fixed_point &position)
    {
        _sL.set_position(position.x() - 16, position.y());
        _sR.set_position(position.x() + 16, position.y());
        _position = position;
    }

    void set_selected(bool select)
    {
        bool changed = false;
        if (_selected && !select)
        {
            _sL = _sprite.create_sprite(0);
            _sR = _sprite.create_sprite(1);
            changed = true;
        }
        else if (!_selected && select)
        {
            _sL = _sprite.create_sprite(2);
            _sR = _sprite.create_sprite(3);
            changed = true;
        }
        if (changed)
        {
            set_position(_position);
            _selected = select;
            _sL.set_z_order(1);
            _sR.set_z_order(1);
            _sL.set_blending_enabled(true);
            _sR.set_blending_enabled(true);
        }
    }

    void set_loading(int frame) // frame in [0-7] for loading, -1 to reset to selected only
    {
        _sL = _sprite.create_sprite(2 * frame + 4);
        _sR = _sprite.create_sprite(2 * frame + 5);
        set_position(_position);
        _sL.set_z_order(1);
        _sR.set_z_order(1);
        _sL.set_blending_enabled(true);
        _sR.set_blending_enabled(true);
    }

  private:
    const bn::sprite_item &_sprite;
    bn::fixed_point _position;
    bn::sprite_ptr _sL;
    bn::sprite_ptr _sR;
    bool _selected;
    bn::sprite_text_generator _generator;
    bn::vector<bn::sprite_ptr, 16> _text;
};

class Logo : MultiSprite
{
  public:
    Logo(const bn::sprite_item &item, const bn::fixed_point &position)
        : MultiSprite(item, position), _original_pos(position)
    {
        set_blending_enabled(true);
    }
    void update_pos()
    {
        if (_clock > _clock_max)
            _clock = 0;
        set_position(_original_pos.x() + bn::sin(_clock / _clock_max) * 5, _original_pos.y());
        _clock += 1;
    }

  private:
    bn::fixed_point _original_pos;
    bn::fixed _clock = 0;
    bn::fixed _clock_max = 150;
};

constexpr int frame_press_trigger = 30;

bool update_status(bool &yes_selected, int frame_press_current);
bool update_display(Button &b_y, Button &b_n, bool swap, bool button_yes_selected, int &frame_confirm_pressed);

void show_screen_verification()
{
    bn::bg_palettes::set_transparent_color(bn::colors::black);

    // Top logo
    Logo logo(bn::sprite_items::ph_pixel_small, bn::fixed_point(0, -65));

    // Warning text
    bn::sprite_text_generator generator_top(verdana9::bold_8x16_sprite_font);
    generator_top.set_blending_enabled(true);
    generator_top.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    bn::vector<bn::sprite_ptr, 64> sprites_top;
    generator_top.generate(0, -45, top_text, sprites_top);

    // Main text
    bn::sprite_text_generator generator_main(verdana9::italic_8x16_sprite_font);
    generator_main.set_blending_enabled(true);
    generator_main.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    bn::vector<bn::vector<bn::sprite_ptr, 64>, nb_lines> sprites_main(nb_lines);
    for (int i = 0; i < nb_lines; ++i)
        generator_main.generate(0, -30 + i * 11, displayed_text[i], sprites_main[i]);

    constexpr int button_y = 65;
    constexpr int button_x = 50;

    bn::sprite_item button_sprite = button_sprites[randomizer.get_int(nb_button_sprites)];
    Button button_Y(button_sprite, bn::fixed_point(-button_x, button_y), false, "+18   Entrer");
    Button button_N(button_sprite, bn::fixed_point(button_x, button_y), true, "-18   Partir");
    bn::core::update();

    bool button_yes_selected = false;
    int frame_press_current = 0;
    while (true)
    {
        logo.update_pos();

        bn::core::update();
        bool swap = update_status(button_yes_selected, frame_press_current);
        bool fully_loaded = update_display(button_Y, button_N, swap, button_yes_selected, frame_press_current);
        if (fully_loaded)
            break;
    }

    // Blink selected button
    Button &selected_button = button_yes_selected ? button_Y : button_N;
    bool toggled = true;
    int current_frame = 0;
    int current_blink = 0;
    constexpr int blink_count = 12;
    constexpr int frame_per_blink = 3;
    while (current_blink < blink_count)
    {
        if (++current_frame > frame_per_blink)
        {
            current_frame = 0;
            toggled = !toggled;
            selected_button.set_loading(toggled ? 7 : -1);
            if (++current_blink > blink_count)
                break;
        }

        logo.update_pos();
        bn::core::update();
    }

    int duration = button_yes_selected ? 10 : 30;
    fade(Fade::OUT, duration);
    current_screen = button_yes_selected ? ScreenType::LOADING : ScreenType::OTHER_GAMES;
}

// return true if a button loaded entirely
bool update_display(Button &b_y, Button &b_n, bool swap, bool button_yes_selected, int &frame_press_current)
{
    if (swap)
    {
        if (button_yes_selected)
        {
            b_y.set_selected(true);
            b_n.set_selected(false);
        }
        else
        {
            b_n.set_selected(true);
            b_y.set_selected(false);
        }
        frame_press_current = 0;
        return false;
    }

    const bool a_start_pressed = bn::keypad::a_pressed() || bn::keypad::start_pressed();
    const bool a_start_held = bn::keypad::a_held() || bn::keypad::start_held();
    // So that when entering screen while pressing A or Start it doesn't start the animation
    if ((frame_press_current == 0 && a_start_pressed) || (frame_press_current > 0 && a_start_held)) // load animation
    {
        ++frame_press_current;
        int sprite_frame = (8 * frame_press_current) / frame_press_trigger;
        if (sprite_frame == 8)
            return true;
        (button_yes_selected ? b_y : b_n).set_loading(sprite_frame);
    }
    else if (frame_press_current > 0) // reset animation
    {
        frame_press_current = 0;
        (button_yes_selected ? b_y : b_n).set_loading(-1);
    }

    return false;
}

// Return true a swap has been done (loading can not increase).
// Disposition is `[Yes] [No]`
bool update_status(bool &yes_selected, int frame_press_current)
{
    // No swapping if pressing
    if (frame_press_current > 0)
        return false;

    // Swap
    if (bn::keypad::select_pressed() || bn::keypad::up_pressed() || bn::keypad::down_pressed())
    {
        yes_selected = !yes_selected;
        return true;
    }
    // No to Yes
    if (!yes_selected && (bn::keypad::l_pressed() || bn::keypad::left_pressed()))
    {
        yes_selected = true;
        return true;
    }
    // Yes to No
    if (yes_selected && (bn::keypad::r_pressed() || bn::keypad::right_pressed()))
    {
        yes_selected = false;
        return true;
    }
    return false;
}