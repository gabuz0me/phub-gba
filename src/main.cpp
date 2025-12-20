#include <bn_core.h>

#include "screen.h"
#include "utils.h"

#ifdef SPLASH_SCREEN
ScreenType current_screen = ScreenType::SPLASH;
constexpr bn::color init_color = bn::colors::white;
#else
ScreenType current_screen = ScreenType::TITLE;
constexpr bn::color init_color = bn::colors::black;
#endif

bn::seed_random randomizer;

int main()
{
    bn::core::init(init_color);

    while (true)
    {
        switch (current_screen)
        {
        case ScreenType::TITLE:
        {
            show_screen_main();
            break;
        }
        case ScreenType::PH_INTRO:
        {
            show_screen_animation();
            break;
        }
        case ScreenType::VERIFICATION:
        {
            show_screen_verification();
            break;
        }
        case ScreenType::LOADING:
        {
            show_screen_loading();
            break;
        }
        case ScreenType::DELACROIX:
        {
            show_screen_delacroix();
            break;
        }
        case ScreenType::OTHER_GAMES:
        {
            show_screen_other_games();
            break;
        }
#ifdef SPLASH_SCREEN
        case ScreenType::SPLASH:
        {
            show_screen_splash();
            break;
        }
#endif
        default:
            break;
        }
    }
}