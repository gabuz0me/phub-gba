#include <bn_size.h>
#include <bn_sprite_item.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_tiles_ptr.h>
#include <bn_vector.h>

#include "multi_sprite.h"

MultiSprite::MultiSprite(const bn::sprite_item &item, bn::fixed x, bn::fixed y)
    : MultiSprite(item, bn::fixed_point(x, y))
{
}

MultiSprite::MultiSprite(const bn::sprite_item &item, const bn::fixed_point &position)
    : _position(position), _item(item), _sprite_count(_item.tiles_item().graphics_count())
{
    for (int i = 0; i < _sprite_count; ++i)
    {
        bn::sprite_ptr sprite = _item.create_sprite();
        sprite.set_tiles(_item.tiles_item().create_tiles(i));
        _sprites.push_back(std::move(sprite));
    }
    _width = _sprites[0].dimensions().width();
    set_position(position);
}

void MultiSprite::set_position(bn::fixed x, bn::fixed y) { set_position(bn::fixed_point(x, y)); }

void MultiSprite::set_position(const bn::fixed_point &position)
{
    const int div = _sprite_count / 2;
    for (int i = 0; i < _sprite_count; ++i)
    {
        int dx;
        if (_sprite_count % 2 == 0)
        {
            dx = (2 * i - _sprite_count + 1) * _width / 2;
        }
        else
        {
            dx = (i - div) * _width;
        }
        _sprites[i].set_position(position.x() + dx, position.y());
    }
}

int MultiSprite::width() const { return _item.shape_size().width() * _item.tiles_item().graphics_count(); }

int MultiSprite::height() const { return _item.shape_size().height(); }

const bn::fixed_point &MultiSprite::position() const { return _position; }
