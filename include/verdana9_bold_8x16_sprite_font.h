#ifndef VERDANA9_BOLD_8x16_SPRITE_FONT_H
#define VERDANA9_BOLD_8x16_SPRITE_FONT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_verdana9_bold_8x16_font.h"
#include "bn_utf8_characters_map.h"

namespace verdana9
{

constexpr bn::utf8_character bold_8x16_sprite_font_utf8_characters[] = {
    "À", "È", "à", "â", "ç", "è", "é", "ê", "ô", "û", "œ", "©", "⋅"}; // ⋅ is copyleft symbol

constexpr int8_t bold_8x16_sprite_font_character_widths[] = {
    3, // 32
    4, // 33 !
    5, // 34 "
    8, // 35 #
    6, // 36 $
    8, // 37 %
    8, // 38 &
    3, // 39 '
    5, // 40 (
    5, // 41 )
    6, // 42 *
    8, // 43 +
    3, // 44 ,
    4, // 45 -
    3, // 46 .
    6, // 47 /
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
    8, // 60 <
    8, // 61 =
    8, // 62 >
    6, // 63 ?
    8, // 64 @
    8, // 65 A
    7, // 66 B
    6, // 67 C
    7, // 68 D
    6, // 69 E
    6, // 70 F
    7, // 71 G
    7, // 72 H
    5, // 73 I
    5, // 74 J
    7, // 75 K
    6, // 76 L
    8, // 77 M
    7, // 78 N
    8, // 79 O
    7, // 80 P
    8, // 81 Q
    7, // 82 R
    6, // 83 S
    6, // 84 T
    7, // 85 U
    7, // 86 V
    8, // 87 W
    7, // 88 X
    7, // 89 Y
    6, // 90 Z
    5, // 91 [
    6, // 92
    5, // 93 ]
    8, // 94 ^
    6, // 95 _
    6, // 96 `
    6, // 97 a
    6, // 98 b
    5, // 99 c
    6, // 100 d
    6, // 101 e
    5, // 102 f
    6, // 103 g
    6, // 104 h
    3, // 105 i
    4, // 106 j
    6, // 107 k
    3, // 108 l
    8, // 109 m
    6, // 110 n
    6, // 111 o
    6, // 112 p
    6, // 113 q
    4, // 114 r
    5, // 115 s
    5, // 116 t
    6, // 117 u
    6, // 118 v
    8, // 119 w
    6, // 120 x
    6, // 121 y
    5, // 122 z
    6, // 123 {
    5, // 124 |
    6, // 125 }
    8, // 126 ~
    8, // À
    6, // È
    6, // à
    6, // â
    5, // ç
    6, // è
    6, // é
    6, // ê
    6, // ô
    6, // û
    8, // œ
    8, // ©
    8, // ⋅
};

constexpr bn::span<const bn::utf8_character>
    bold_8x16_sprite_font_utf8_characters_span(bold_8x16_sprite_font_utf8_characters);

constexpr auto bold_8x16_sprite_font_utf8_characters_map =
    bn::utf8_characters_map<bold_8x16_sprite_font_utf8_characters_span>();

constexpr bn::sprite_font bold_8x16_sprite_font(bn::sprite_items::verdana9_bold_8x16_font,
                                                bold_8x16_sprite_font_utf8_characters_map.reference(),
                                                bold_8x16_sprite_font_character_widths);

} // namespace verdana9

#endif
