#ifndef COMMON_H
#define COMMON_H

enum class ScreenType : int
{
    MAIN,
    INTRO,
    ANIMATION,
    PROMPT,
    OTHER_GAMES,
    LOADING,
    DELACROIX,
};

extern ScreenType current_screen;

// static int VERSION = 0;

#endif