#ifndef SCREEN_H
#define SCREEN_H

#include <bn_keypad.h>

void show_screen_main(void);
void show_screen_delacroix(void);
void show_screen_animation(void);

enum class ScreenType : int
{
    TITLE,
    PH_INTRO,
    PROMPT,
    OTHER_GAMES,
    LOADING,
    DELACROIX,
};

inline bool a_or_start_pressed(void) { return bn::keypad::a_pressed() || bn::keypad::start_pressed(); }

extern ScreenType current_screen;

#endif