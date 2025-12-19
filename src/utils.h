#ifndef UTILS_H
#define UTILS_H

#include <bn_color.h>
#include <bn_colors.h>
#include <bn_seed_random.h>
#include <bn_sprite_item.h>
#include <bn_vector.h>

extern bn::seed_random randomizer;

template <class T> inline T smoothstep(T x) { return (T(3.) - T(2.) * x) * x * x; }

template <int NB> void generate_random_order(bn::vector<int, NB> &table)
{
    table.resize(NB);
    bn::vector<bool, NB> was_picked(NB, false);
    for (int i = 0; i < NB; ++i)
    {
        int random_index = randomizer.get_int(NB);
        while (was_picked[random_index])
            random_index = (random_index + 1) % NB;
        table[i] = random_index;
        was_picked[random_index] = true;
    }
}

template <class T> T map(T t, T x1, T x2, T y1, T y2)
{
    const T x_ = x2 - x1;
    const T t_ = t - x1;
    const T y_ = y2 - y1;
    return y1 + (t_ * y_) / x_;
}

bn::sprite_palette_item simple_text_palette(bn::color color_main, bn::color color_other = bn::colors::black);

constexpr bn::color rgb_to_rgb15(int r, int g, int b)
{
    r = (r * 31) / 255;
    g = (g * 31) / 255;
    b = (b * 31) / 255;
    return bn::color(r, g, b);
}

namespace bn::colors
{
constexpr bn::color phub(rgb_to_rgb15(247, 151, 29)); // The Holy Numbers..!
}

#endif