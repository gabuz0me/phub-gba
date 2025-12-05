#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "bn_vector.h"
#include "verdana9_bold_8x16_sprite_font.h"
#include "verdana9_italic_8x16_sprite_font.h"
#include "verdana9_normal_8x16_sprite_font.h"

#include "multi_sprite.h"
#include "screen.h"

#include "bn_sprite_items_ph_pixel_small.h"

#include "text/text_verification_fr_verdana9_italic_8x16_sprite_font.h"
// #include "text/text_verification_en_verdana9_italic_8x16_sprite_font.h"
constexpr int nb_lines = sizeof(displayed_text) / sizeof(displayed_text[0]);

// constexpr char top_text[] = "This is an adult website";
constexpr char top_text[] = "Ceci est un site web destiné aux adultes!";

void show_screen_verification()
{
    // Top logo
    MultiSprite logo(bn::sprite_items::ph_pixel_small, 0, -65);

    // Warning text
    bn::sprite_text_generator generator_top(verdana9::bold_8x16_sprite_font);
    generator_top.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    bn::vector<bn::sprite_ptr, 64> sprites_top;
    generator_top.generate(0, -45, top_text, sprites_top);

    // Main text
    bn::sprite_text_generator generator_main(verdana9::italic_8x16_sprite_font);
    generator_main.set_alignment(bn::sprite_text_generator::alignment_type::CENTER);
    bn::vector<bn::vector<bn::sprite_ptr, 64>, nb_lines> sprites_main(nb_lines);
    for (int i = 0; i < nb_lines; ++i)
        generator_main.generate(0, -30 + i * 11, displayed_text[i], sprites_main[i]);

    while (true)
    {
        bn::core::update();
    }
}