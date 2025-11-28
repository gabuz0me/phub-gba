#ifndef SCREEN_H
#define SCREEN_H

void show_screen_main(void);
void show_screen_delacroix(void);
void show_screen_animation(void);

enum class ScreenType : int
{
    TITLE,
    ANIMATION,
    PROMPT,
    OTHER_GAMES,
    LOADING,
    DELACROIX,
};

extern ScreenType current_screen;

#endif