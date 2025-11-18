#include <bn_core.h>

#include "common.h"
#include "main_screen.h"

int main()
{
    bn::core::init();
    // screen_type = MAIN;

    //

    while (true)
    {
        switch (screen_type)
        {
        case ScreenType::MAIN:
        {
            show_main_screen();
            break;
        default:
            break;
        }
        }
    }
}