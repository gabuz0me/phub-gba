#!/usr/bin/env python

from subprocess import check_output, run

json = '{"type":"sprite","height":64,"width":32}'

command_list = "aseprite -b --all-layers --list-layer-hierarchy cartridge.aseprite"
out = check_output(command_list.split()).decode()
layers = [layer[:-1] for layer in out.split() if layer.endswith("/")]

for visible_nb, visible_layer in enumerate(layers[1:], 1):
    print(f"Exporting {visible_layer}... ", end="")
    visible_layer = visible_layer.lower()
    command = "aseprite -b --all-layers "
    for hide_nb, hide_name in enumerate(layers[1:], 1):
        if hide_nb != visible_nb:
            command += f"--ignore-layer {hide_name} "
    command += "--crop -8,-8,96,64 "
    command += "cartridge.aseprite "
    command += f"--save-as {visible_layer}.bmp "
    # command += "-p " # Debug
    _ = run(command.split())
    _ = run(
        f"magick {visible_layer}.bmp -define bmp:format=bmp3 -strip -colors 16 -type Palette {visible_layer}.bmp".split(),
    )

    with open(f"{visible_layer}.json", "w") as file:
        _ = file.write(json)
    print("Done")
