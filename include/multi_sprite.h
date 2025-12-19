#ifndef MULTISPRITE_H
#define MULTISPRITE_H

#include <bn_sprite_item.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_tiles_ptr.h>
#include <bn_vector.h>

constexpr int NB = 8;

class MultiSprite
{
  public:
    MultiSprite(const bn::sprite_item &item, bn::fixed x = 0, bn::fixed y = 0);
    MultiSprite(const bn::sprite_item &item, const bn::fixed_point &position);
    void set_position(bn::fixed x, bn::fixed y);
    void set_position(const bn::fixed_point &position);

    void set_blending_enabled(bool);
    int width() const;
    int height() const;
    const bn::fixed_point &position() const;
    const bn::vector<bn::sprite_ptr, NB> &get_sprites() const { return _sprites; }

  private:
    bn::fixed_point _position;
    bn::vector<bn::sprite_ptr, NB> _sprites;
    const bn::sprite_item &_item;
    const int _sprite_count;
    int _width;
};
#endif
