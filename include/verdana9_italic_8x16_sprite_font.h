#ifndef VERDANA9_ITALIC_8x16_SPRITE_FONT_H
#define VERDANA9_ITALIC_8x16_SPRITE_FONT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_verdana9_italic_8x16_font.h"
#include "bn_utf8_characters_map.h"

namespace verdana9
{

constexpr int8_t italic_8x16_sprite_font_character_widths[] = {
    3, // 32
    4, // 33 !
    4, // 34 "
    7, // 35 #
    6, // 36 $
    8, // 37 %
    7, // 38 &
    2, // 39 '
    4, // 40 (
    5, // 41 )
    6, // 42 *
    7, // 43 +
    3, // 44 ,
    4, // 45 -
    3, // 46 .
    5, // 47 /
    6, // 48 0
    6, // 49 1
    6, // 50 2
    6, // 51 3
    6, // 52 4
    6, // 53 5
    6, // 54 6
    6, // 55 7
    6, // 56 8
    6, // 57 9
    4, // 58 :
    4, // 59 ;
    7, // 60 <
    7, // 61 =
    7, // 62 >
    5, // 63 ?
    8, // 64 @
    6, // 65 A
    6, // 66 B
    6, // 67 C
    7, // 68 D
    6, // 69 E
    6, // 70 F
    7, // 71 G
    7, // 72 H
    5, // 73 I
    5, // 74 J
    7, // 75 K
    5, // 76 L
    8, // 77 M
    7, // 78 N
    7, // 79 O
    5, // 80 P
    7, // 81 Q
    6, // 82 R
    6, // 83 S
    6, // 84 T
    7, // 85 U
    6, // 86 V
    8, // 87 W
    6, // 88 X
    6, // 89 Y
    6, // 90 Z
    6, // 91 [
    4, // 92 backslash
    5, // 93 ]
    7, // 94 ^
    7, // 95 _
    6, // 96 `
    5, // 97 a
    6, // 98 b
    5, // 99 c
    6, // 100 d
    5, // 101 e
    5, // 102 f
    6, // 103 g
    6, // 104 h
    3, // 105 i
    5, // 106 j
    5, // 107 k
    3, // 108 l
    8, // 109 m
    6, // 110 n
    5, // 111 o
    7, // 112 p
    6, // 113 q
    4, // 114 r
    6, // 115 s
    4, // 116 t
    6, // 117 u
    6, // 118 v
    8, // 119 w
    5, // 120 x
    6, // 121 y
    5, // 122 z
    6, // 123 {
    4, // 124 |
    6, // 125 }
    7, // 126 ~
};

constexpr bn::span<const bn::utf8_character> italic_8x16_sprite_font_utf8_characters_span;

constexpr auto italic_8x16_sprite_font_utf8_characters_map =
    bn::utf8_characters_map<italic_8x16_sprite_font_utf8_characters_span>();

constexpr bn::sprite_font italic_8x16_sprite_font(bn::sprite_items::verdana9_italic_8x16_font,
                                                  italic_8x16_sprite_font_utf8_characters_map.reference(),
                                                  italic_8x16_sprite_font_character_widths);

} // namespace verdana9

#endif
