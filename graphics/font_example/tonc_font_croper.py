#!/usr/bin/env python

import sys
from collections import Counter
from pathlib import Path

import numpy as np
from PIL import Image

extra_letters = "ÀÈàâçèéêôûœ\u202f©$  "  # Extra letters for my custom font


def parse_image(path: Path):
    print(path.stem)
    color_counter: Counter[int] = Counter()
    image = Image.open(str(path))
    for pixel_x in range(image.width):
        for pixel_y in range(image.height):
            color = image.getpixel((pixel_x, pixel_y))
            color_counter.update([color])

    colors = sorted(
        color_counter.items(),
        key=lambda t: t[1],
    )

    color_transp = colors[-1][0]
    # print(colors[:-1], color_transp)

    M = 16
    N = 8
    im = np.array(image)
    tiles = [
        im[x : x + M, y : y + N]
        for x in range(0, im.shape[0], M)
        for y in range(0, im.shape[1], N)
    ]

    # print(tiles[1])
    # print(tiles[18])

    # return

    width_list: list[int] = []

    for nb, tile in enumerate(tiles):
        row: list[int] = tile[0]
        # print(row, end="")
        for i, value in enumerate(row):
            if value == color_transp:
                width_list.append(i)
                break
        else:
            width_list.append(len(row))

    with open(f"{path.stem}.txt", "w") as output_file:
        for index, length in enumerate(width_list, 32):
            if index == 127:  # backspace character
                # print("====== 127 ======")
                continue
            line = f"{length}, // "
            if index < 127:
                line += f"{index} {chr(index)}"
            # else:
            #     line += f"{extra_letters[index - 128]}"
            line += "\n"
            # print(line, end="")
            output_file.write(line)


for path in sys.argv[1:]:
    parse_image(Path(path))
