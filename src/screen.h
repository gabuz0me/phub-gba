#ifndef SCREEN_H
#define SCREEN_H

#include <bn_keypad.h>
#include <bn_seed_random.h>

void show_screen_main();
void show_screen_animation();
void show_screen_verification();
void show_screen_delacroix();
void show_screen_other_games();

enum class ScreenType : int
{
    TITLE,
    PH_INTRO,
    VERIFICATION,
    LOADING,
    DELACROIX,
    OTHER_GAMES,
};

inline bool a_or_start_pressed(void) { return bn::keypad::a_pressed() || bn::keypad::start_pressed(); }

extern ScreenType current_screen;
extern bn::seed_random randomizer;

#endif