#!/usr/bin/env python

"""
This scripts extract each layer of the `cartridge.aseprite` file into an image
for the "other games" screen. It then creates the appropriate `cartridges.h` so
that I don't have to change anything on the cpp side if I add or remove images
of fake GBA games.

It uses Aseprite. You can buy the software and/or build it yourself.
It uses ImageMagick for image conversion.

It may be one of the ugliest Python script I ever wrote, but hey, it's working
fine for my need.
"""

import os
import re
from glob import glob
from pathlib import Path
from subprocess import check_output, run
from sys import argv

RM = "-r" in argv
here = Path(__file__).parent
os.chdir(here)
json = '{"type":"sprite","height":64,"width":32}'
aseprite = "aseprite"  # Put full executable path here if needed
path_cartridges_h = here / "../../../include/cartridges.h"

# === Clean Folder ===
if RM:
    print("Cleaning... ", end="")
    for file in glob("*.json") + glob("*.bmp"):
        os.remove(file)
    if path_cartridges_h.exists():
        os.remove(path_cartridges_h)
    print("Done")
    exit(0)

# === Get all layers that are folders ===
# Layers starting with `_` are to be always hidden (debug and template)
# Layers starting with `+` are to be always shown (cartridge contour, maybe some effects later, who knows)
cartridge_path = here / "cartridge.aseprite"
command_list = f"{aseprite} -b --all-layers --list-layer-hierarchy {cartridge_path}"
out = check_output(command_list.split()).decode()
layers_all = {
    layer[:-1]  # Remove final '/'
    for layer in out.split()
    if layer.endswith("/") and not layer.startswith("+")
}
layers_to_hide = {layer for layer in layers_all if layer.startswith("_")}
layers_to_show = layers_all - layers_to_hide

# === Exporting images and creating json files ===
nb_too_many_colors = 0
for layer_to_show in layers_to_show:
    layers_to_hide_current = layers_all - {layer_to_show}
    image_name = layer_to_show.lower()
    print(f"Exporting {layer_to_show}... ", end="")

    # --- 1. Exporting image ---
    command = f"{aseprite} -b --all-layers "
    for layer_to_hide in layers_to_hide_current:
        command += f"--ignore-layer {layer_to_hide} "
    command += "--crop -8,-8,96,64 "
    command += "cartridge.aseprite "
    command += f"--save-as {image_name}.bmp "
    # command += "-p "  # Debug
    _ = run(command.split())

    # --- 2. Check if valid number of colors ---
    out = check_output(f"magick identify -verbose {image_name}.bmp".split()).decode()
    match = re.match(r".*Colors: (\d*).*", out, re.DOTALL)  # Don't judge pls
    if match:
        nb_colors = int(match.group(1))
        if nb_colors > 16:
            nb_too_many_colors += 1
            print(f"TOO MANY COLORS ({nb_colors})..! ", end="")

    # --- 3. Convert to indexed ---
    _ = run(
        f"magick {image_name}.bmp -define bmp:format=bmp3 -strip -colors 16 -type Palette {image_name}.bmp".split()
    )

    with open(f"{image_name}.json", "w") as file:
        _ = file.write(json)
    print("Done")

# === Creating `cartridges.h` file ===
print("\nCreating header file... ", end="")
with open(path_cartridges_h, "w") as f:
    for layer_to_show in layers_to_show:
        _ = f.write(f'#include "bn_sprite_items_{layer_to_show.lower()}.h"\n')
    _ = f.write("bn::sprite_item all_cartridges[] = {\n")
    for layer_to_show in layers_to_show:
        _ = f.write(f"bn::sprite_items::{layer_to_show.lower()}, //\n")
    _ = f.write("};\n")
    _ = f.write(
        "constexpr int all_cartridge_size = sizeof(all_cartridges) / sizeof(all_cartridges[0]);\n"
    )
print("Done!")

# === We cool? ===
if nb_too_many_colors > 0:
    print(f"\n{nb_too_many_colors} images won't be displayed well! Please fix :(")
else:
    print("\nAll done! Should be working ;)")
