#ifndef VERDANA9_NORMAL_8x16_SPRITE_FONT_H
#define VERDANA9_NORMAL_8x16_SPRITE_FONT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_verdana9_normal_8x16_font.h"
#include "bn_utf8_characters_map.h"

namespace verdana9
{

constexpr bn::utf8_character normal_8x16_sprite_font_utf8_characters[] = {
    "À", "È", "à", "â", "ç", "è", "é", "ê", "ô", "û", "œ", "¬", "…", "©", "⋅"}; // ⋅ is copyleft symbol

constexpr int8_t normal_8x16_sprite_font_character_widths[] = {
    2, // 32
    2, // 33 !
    4, // 34 "
    6, // 35 #
    6, // 36 $
    8, // 37 %
    7, // 38 &
    2, // 39 '
    4, // 40 (
    4, // 41 )
    6, // 42 *
    6, // 43 +
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
    3, // 58 :
    3, // 59 ;
    6, // 60 <
    6, // 61 =
    6, // 62 >
    5, // 63 ?
    8, // 64 @
    7, // 65 A
    6, // 66 B
    7, // 67 C
    7, // 68 D
    6, // 69 E
    6, // 70 F
    7, // 71 G
    7, // 72 H
    4, // 73 I
    4, // 74 J
    6, // 75 K
    6, // 76 L
    8, // 77 M
    7, // 78 N
    8, // 79 O
    6, // 80 P
    8, // 81 Q
    6, // 82 R
    6, // 83 S
    7, // 84 T
    7, // 85 U
    7, // 86 V
    8, // 87 W
    6, // 88 X
    6, // 89 Y
    6, // 90 Z
    3, // 91 [
    5, // 92 backslash
    3, // 93 ]
    6, // 94 ^
    6, // 95 _
    5, // 96 `
    5, // 97 a
    5, // 98 b
    5, // 99 c
    5, // 100 d
    5, // 101 e
    5, // 102 f
    5, // 103 g
    5, // 104 h
    2, // 105 i
    4, // 106 j
    5, // 107 k
    2, // 108 l
    8, // 109 m
    5, // 110 n
    5, // 111 o
    5, // 112 p
    5, // 113 q
    4, // 114 r
    5, // 115 s
    5, // 116 t
    5, // 117 u
    5, // 118 v
    6, // 119 w
    5, // 120 x
    5, // 121 y
    4, // 122 z
    6, // 123 {
    4, // 124 |
    6, // 125 }
    6, // 126 ~
    7, // À
    6, // È
    5, // à
    5, // â
    5, // ç
    5, // è
    5, // é
    5, // ê
    5, // ô
    5, // û
    8, // œ
    3, //  
    3, //  
    8, // ©
    8, // ⋅ copyleft
};

constexpr bn::span<const bn::utf8_character>
    normal_8x16_sprite_font_utf8_characters_span(normal_8x16_sprite_font_utf8_characters);

constexpr auto normal_8x16_sprite_font_utf8_characters_map =
    bn::utf8_characters_map<normal_8x16_sprite_font_utf8_characters_span>();

constexpr bn::sprite_font normal_8x16_sprite_font(bn::sprite_items::verdana9_normal_8x16_font,
                                                  normal_8x16_sprite_font_utf8_characters_map.reference(),
                                                  normal_8x16_sprite_font_character_widths);

} // namespace verdana9

#endif
