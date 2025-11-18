#ifndef COMMON_H
#define COMMON_H

typedef enum
{
    MAIN,
    INTRO,
    ANIMATION,
    PROMPT,
    OTHER_GAMES,
    LOADING,
    FINAL
} ScreenType;

static ScreenType screen_type(MAIN);

// static int VERSION = 0;

#endif