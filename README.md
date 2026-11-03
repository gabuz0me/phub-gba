<div align="center">

**[English Version](README.en.md)**

# PHUB-GBA

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa-link] [![CeCILL 2.10][cecill-shield]][cecill-link] [![Butano][butano-shield]][butano-link]

![intro](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/intro.gif)

*« Ton site préféré sur ta console préférée !»*

</div>

---

## Qu'est-ce que c'est que ce truc ??

Alors c'est un projet troll que j'ai fait pour un pote. Comme PH a été banni en France en 2025 (je crois) (sous prétexte de protéger les enfants (ce qui est d'un cynisme sans nom (mais ça n'est pas le sujet))), je voulais faire un "jeu vidéo" qui fait mine d'accéder au site après moult bruits de modem se connectant et un long chargement, pour finalement afficher le message que les internautes basé⋅e⋅s en France obtiennent quand iels essaient d'accéder au site susmentioné. Oui je sais, c'est hilarant.

Même si le jeu contient pas mal de logo du site, **il n'est absolument pas NSFW**. Dans le sens de la nudité et tout hein, j'imagine qu'avoir le logo PH au taf ça ne fait pas pro non plus...

## Comment y jouer ?

Télécharge le fichier .gba (avec ou sans splashscreen), lance-le dans ton émulateur favoris et zou.

Ou mieux ! Chauffe-toi, télécharge et imprime [la boîte](art/box.svg) (modifie le svg pour avoir le "vrai" logo :wink:) et les patrons des différents accessoires (étiquettes, petite boîte, le support de cartouche de la boîte). Après tu bricoles tout ça, tu flashes une cartouche et là tu vis l'expérience à 100%, comme Nintendo l'aurait voulu :pray:

## Je dev, comment je build la ROM ?

Alors déjà, le code, il est pas beau. Il a été fini sous monster blanche tard la nuit pour que je puisse délivrer le cadeau à temps pour mon bro. Je ne l'ai pas trop nettoyé (le code, pas le bro) après parce que flemme ; considère-toi comme prévenu. Oh et si tu es un employeur qui regarde mon portefolio, stp ne refuse pas de m'embaucher parce que tu as vu l'état du code, je fais mieux en général hein.

Donc, pour le build : Moi je dev sous gnunux (Arch, btw), j'ai pas testé sous Windoz ou WSL. Il faut installer [butano](https://github.com/GValiente/butano) :heart: et avoir [devkitARM](https://devkitpro.org/wiki/Getting_Started) configuré correctement. Voir les [guides](https://gbadev.net/tonc/) pour plus d'info.

Quand tout est bon, il te faut juste lancer `make` à la racine du projet et zou. J'ai aussi utilisé [bear](https://github.com/rizsotto/Bear) pour créer le `compile_commands.json` pour CLang : `bear -- cmake -j64`

Si tu veux debug et tout, regarde dans le dossier `.vscode` il y a deux-trois machins.

## Comment qu'on bidouille ça ?

### Plus d'images de fausses cartouches !

Dans `graphics/other_games/cartridges/`, tu peux ajouter plus de calques à [`cartridge.aseprite`](graphics/other_games/cartridges/cartridge.aseprite) et lancer [`cartridge_exporter.py`](graphics/other_games/cartridges/cartridge_exporter.py) pour automatiquement créer les fichiers images et de code qui seront utilisés dans le projet.

### C'est quoi cet écran de démarrage de salopard ?

En fait, j'ai ajouté au lancement du jeu un écran de démarrage (*splashscreen*) avec la bonne grosse tête de mon bro dans une photo honteuse dont seul l'alcool et le manque de sommeil ont le secret. Donc je ne veux pas que ce soit disponible au grand public et ai donc remplacé l'image par un [bmp du meilleur goût](graphics/splash_screen.bmp). C'est ça qu'il faut modifier, ou alors juste commenter `SPLASH_SCREEN` dans [`screen.h`](src/screen.h#L6) pour désactiver totalement l'écran de démarrage.

### Wow tu t'es chauffé de zinz' pour la fausse image d'écran d'accueil !

Oh, tu parles de [celle-là](graphics/loading/ph_main_page.bmp) disponible en haute définition [ici](graphics/loading/ph_main_page.xcf) (format GIMP) ? Merci, tu as l'œil dis-donc ! ^^

## Crédits

Ce machin est bien évidemment une parodie et n'a pour intention de ne violer aucun droit d'auteur. Les logos et marques sont la propriété de leurs ayant-droits et sont utilisés ici dans un cadre explicite de parodie, comme le droit le permet.

- Le gimmick vidéo de lancement d'une vidéo PH a été rippé depuis [YouTube](https://www.youtube.com/watch?v=2MDlXYPHOo8)
- Les images de la [fausse page d'accueil du site](graphics/loading/ph_main_page.bmp) viennent de [Pexels](https://www.pexels.com/)
- Les effets sonores viennent de [Pixabay](https://pixabay.com/)
- la "Trololo song" vient de [YouTube](https://www.youtube.com/watch?v=j2yCfIHFRhI), © Eduard Khil
- [Oh Yeah](https://www.youtube.com/watch?v=6jJkdRaa04g), © Yello
- "Input Prompts Pixel", par [Kenney](https://kenney.nl/assets/input-prompts-pixel)
- Toutes les autres images, y compris les cartouches sont dessinés main et sont sous licence [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license.

---

## Visuels du jeu

| D'autres jeux ! | Chargement du site... | Accès suspendu |
|:-:|:-:|:-:|
| ![other games](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/other_games.png) | ![loading](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/loading.png) | ![access forbidden](https://raw.githubusercontent.com/gabuz0me/images/refs/heads/main/phub-gba/acces_suspendu.png) |



[cc-by-sa-link]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/Licence_des_images-CC%20BY--SA%204.0-lightgrey.svg
[cecill-link]: https://cecill.info/licences/Licence_CeCILL_V2.1-en.html
[cecill-shield]: https://img.shields.io/badge/Licence_du_code-CeCILL%202.1-lightgrey.svg
[butano-link]: https://github.com/GValiente/butano
[butano-shield]: https://img.shields.io/badge/Fait_avec_butano-grey?logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMzIwbW0iIGhlaWdodD0iNjQwbW0iIHZlcnNpb249IjEuMSIgdmlld0JveD0iMCAwIDMyMCA2NDAiIHhtbDpzcGFjZT0icHJlc2VydmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0ibTI4OSAxMzdjNy4xIDcuMiAxMSAxNSAxMSAyM3YzODBjMWUtNSAzMy02MyA2MC0xNDAgNjAtNzcgMWUtNSAtMTQwLTI3LTE0MC02MGw3ZS02IC0zODBjLTdlLTYgLTkuNCA1LjEtMTggMTQtMjZsLTguNy0xNWMtNi4zLTExIDQuMS0yOSAyMy00MCAxOS0xMSA0MC0xMSA0Ni0wLjI0bDE1IDI1YzYuNy0xLjEgMTQtMiAyMS0yLjd2LTUxYzAtMTEgMTMtMjAgMzAtMjAgMTctNmUtNiAzMCA5IDMwIDIwdjUxYzE4IDEuNyAzNCA0LjggNDkgOWwxMS0yMGM0LjctOC4xIDE5LTguMyAzMy0wLjUyIDE0IDcuOCAyMSAyMSAxNiAyOXoiIGZpbGw9IiNmZmYiLz48L3N2Zz4K