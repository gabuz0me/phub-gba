#!/usr/bin/env python

from glob import glob
from os import chdir, remove
from pathlib import Path
from subprocess import check_output, run
from sys import argv

DEBUG = "-d" in argv
RM = "-r" in argv

here = Path(__file__).parent
json = '{"type":"sprite","height":64,"width":32}'
aseprite = "aseprite"  # Put full executable path here if needed

# === Clean Folder ===
if RM:
    print("Cleaning json and bmp... ", end="")
    chdir(here)
    for file in glob("*.json") + glob("*.bmp"):
        remove(file)
    print("Done")
    exit(0)

# === Get all layers that are folders ===
# Layers starting with `_` are to be always hidden (debug and template)
# Layers starting with `+` are to be always shown (cartridge contour, maybe some effects later, who knows)
cartridge_path = here / "cartridge.aseprite"
command_list = f"{aseprite} -b --all-layers --list-layer-hierarchy {cartridge_path}"
out = check_output(command_list.split()).decode()
layers_all = {
    layer[:-1]
    for layer in out.split()
    if layer.endswith("/") and not layer.startswith("+")
}
layers_to_hide = {layer for layer in layers_all if layer.startswith("_")}
layers_to_show = layers_all - layers_to_hide

if DEBUG:
    print("\tLayers show:")
    print("\n".join(layers_to_show))
    print("\tLayers hide:")
    print("\n".join(layers_to_hide))

for layer_to_show in layers_to_show:
    layers_to_hide_current = layers_to_hide | (layers_to_show - {layer_to_show})

    print(f"Exporting {layer_to_show}... ", end="")
    command = f"{aseprite} -b --all-layers "
    for layer_to_hide in layers_to_hide_current:
        command += f"--ignore-layer {layer_to_hide} "
    command += "--crop -8,-8,96,64 "
    command += "cartridge.aseprite "
    command += f"--save-as {layer_to_show.lower()}.bmp "
    # command += "-p "  # Debug
    _ = run(command.split())
    _ = run(
        f"magick {layer_to_show.lower()}.bmp -define bmp:format=bmp3 -strip -colors 256 -type Palette {layer_to_show.lower()}.bmp".split(),
    )

    with open(f"{layer_to_show.lower()}.json", "w") as file:
        _ = file.write(json)
    print("Done")

print("Creating file... ", end="")
with open(here / "../../../include/cartridges.h", "w") as f:
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
