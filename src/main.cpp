#include <bn_core.h>

#include "screen.h"

ScreenType current_screen = ScreenType::TITLE;

int main()
{
    bn::core::init();

    while (true)
    {
        switch (current_screen)
        {
        case ScreenType::TITLE:
        {
            show_screen_main();
            break;
        }
        case ScreenType::ANIMATION:
        {
            show_screen_animation();
            break;
        }
        case ScreenType::DELACROIX:
        {
            show_screen_delacroix();
            break;
        }
        default:
            break;
        }
    }
}