#include <bn_core.h>

#include "common.h"
#include "screen.h"

ScreenType current_screen = ScreenType::MAIN;

int main()
{
    bn::core::init();

    while (true)
    {
        switch (current_screen)
        {
        case ScreenType::MAIN:
        {
            show_screen_main();
            break;
        }
        case ScreenType::DELACROIX:
        {
            show_screen_delacroix();
            break;
        }
        case ScreenType::ANIMATION:
        {
            show_screen_intro();
            break;
        }
        default:
            break;
        }
    }
}