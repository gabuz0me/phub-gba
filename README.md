# PHUB-GBA

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]
[![CeCILL 2.10][cecill-shield]][cecill]

![intro](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/intro.gif)

---

## What's this??

This is a troll project I made for a friend of mine. The joke was to have a GBA game about an adult-only website. This project is **not NSFW** btw. Even though there's a lot of PH logo everywhere...

As PH was banned in France, where my bro and I live, I wanted to have a fake PH game with a website loading and ultimately failing due to the website being banned here. Don't judge please.

## How to play?

Just download the .gba file, run it your favorite emulator and you're good to go.

Or better: Download the [box art](art/box.svg), the insert tray, the cartridge box art, the cartridge label, print them all, fold and glue them and create your very own PHUB-GBA box for a stunning experience! Then, flash the ROM on a GBA cartridge and play it on a GBA like this was an original product!

## How to build?

Okay first: The code is messy. Like for real. I finished it in a hell of a rush, and didn't clean it after I offered the game to my pal. You've been warned. Don't refuse to hire me if you've seen that. I swear I can do better.

To build it, you need to have [butano](https://github.com/GValiente/butano) installed and [devkitARM](https://devkitpro.org/wiki/Getting_Started) properly configured. See [guides](https://gbadev.net/tonc/) about GBA dev for more info.

The variable `LIBBUTANO` must be set according to your installation in the Makefile.

When everything is done, just run `make` and voilà.

## How to tweak?

### More cartridges!

In `graphics/other_games/cartridges/`, you can add more layers to the `cartridge.aseprite` file and run `cartridge_exporter.py` to automatically create the cartridges images showcased in the final screen.

### What is that unused `screen_splash.cpp`?

Well, I added a splash screen to the game I built for my mate with their big head on it, but I don't want it to be publicly available. So you can define `SPLASH_SCREEN` in [`screen.h`](src/screen.h#L6) and add your own `splash_screen.bmp` in `graphics/` so that it's used when starting the game.

## Credits

This work is a parody. No copyright infringement intended. The logos and trademarks parodied here belong to the beneficiaries.

- PHub iconic intro video and sound was ripped on [YouTube](https://www.youtube.com/watch?v=2MDlXYPHOo8)
- Images for the fake PH webpage are from [Pexels](https://www.pexels.com/)
- Sounds effects are from [Pixabay](https://pixabay.com/)
- "Trololo song" found on [YouTube](https://www.youtube.com/watch?v=j2yCfIHFRhI), © Eduard Khil
- [Oh Yeah](https://www.youtube.com/watch?v=6jJkdRaa04g), © Yello
- Awesome button design by [Kenney](https://kenney.nl/assets/input-prompts-pixel-16)
- All other images, especially the cartridges and button sprites were drawn by me and are under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license.

---

## More visuals

|                                                Other games!                                                |                                            Website loading!                                            |
| :--------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------: |
| ![other games](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/other_games.png) | ![other games](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/loading.png) |



[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/Image%20License-CC%20BY--SA%204.0-lightgrey.svg
[cecill]: https://cecill.info/licences/Licence_CeCILL_V2.1-en.html
[cecill-shield]: https://img.shields.io/badge/Code%20License-CeCILL%202.1-lightgrey.svg
