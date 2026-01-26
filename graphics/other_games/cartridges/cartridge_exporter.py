#!/usr/bin/env python

from pathlib import Path
from subprocess import check_output, run

here = Path(__file__)
json = '{"type":"sprite","height":64,"width":32}'
aseprite = "aseprite"  # Put full executable path here if needed

cartridge_path = here / "../cartridge.aseprite"
command_list = f"{aseprite} -b --all-layers --list-layer-hierarchy {cartridge_path}"
out = check_output(command_list.split()).decode()
layers = [layer[:-1] for layer in out.split() if layer.endswith("/")]

for visible_nb, visible_layer in enumerate(layers[1:], 1):
    print(f"Exporting {visible_layer}... ", end="")
    visible_layer = visible_layer.lower()
    command = f"{aseprite} -b --all-layers "
    for hide_nb, hide_name in enumerate(layers[1:], 1):
        if hide_nb != visible_nb:
            command += f"--ignore-layer {hide_name} "
    command += "--crop -8,-8,96,64 "
    command += "cartridge.aseprite "
    command += f"--save-as {visible_layer}.bmp "
    # command += "-p "  # Debug
    _ = run(command.split())
    _ = run(
        f"magick {visible_layer}.bmp -define bmp:format=bmp3 -strip -colors 16 -type Palette {visible_layer}.bmp".split(),
    )

    with open(f"{visible_layer}.json", "w") as file:
        _ = file.write(json)
    print("Done")

print("Creating file... ", end="")
with open(here.parent / "../../../include/cartridges.h", "w") as f:
    for layer in layers[1:]:
        _ = f.write(f'#include "bn_sprite_items_{layer.lower()}.h"\n')

    _ = f.write("bn::sprite_item all_cartridges[] = {\n")
    for layer in layers[1:]:
        _ = f.write(f"bn::sprite_items::{layer.lower()}, //\n")
    _ = f.write("};\n")
    _ = f.write(
        "constexpr int all_cartridge_size = sizeof(all_cartridges) / sizeof(all_cartridges[0]);\n"
    )
print("Done!")
