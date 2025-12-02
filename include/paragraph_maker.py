#!/usr/bin/env python3

import re
import sys
from pathlib import Path
from re import Pattern

if len(sys.argv) != 4:
    print("Usage: ./paragraph_maker.py <width> <font_header.h> <textfile>")
    exit(1)

max_width = int(sys.argv[1])
header_path = Path(sys.argv[2])
text_file = Path(sys.argv[3])

with open(header_path, "r", encoding="utf-8") as f:
    header = f.read()

size_finder: Pattern[str] = re.compile(
    r".*constexpr int8_t \w*_widths\[\] = \{(.*?)\};.*",
    re.M | re.DOTALL,
)
entries: list[str] = size_finder.match(header).group(1).split("\n")  # pyright: ignore[reportOptionalMemberAccess]

width_dict: dict[str, int] = {}
dict_parser = re.compile(r"\s*(\d+),\s*//\s*(\d*)\s*(.*)$")
for entry in entries:
    match = dict_parser.match(entry)
    if match:
        width: int = int(match.group(1))
        character: str = match.group(3).replace("backslash", "\\")
        if character == "":
            character = " "
        width_dict[character] = width

# print(width_dict)

with open(text_file, "r", encoding="utf-8") as file:
    text_lines = [line.rstrip("\n") for line in file.readlines()]


def word_size(word: str) -> int:
    total = 0
    for letter in word:
        total += width_dict[letter]
    return total


final_text_list: list[str] = []
final_size_list: list[int] = []
space_size = width_dict[" "]
for line in text_lines:
    current_line = ""
    current_size = 0
    is_first_word = True
    words = line.split(" ")
    to_skip = 0
    for word_index in range(len(words)):
        if to_skip > 0:
            to_skip -= 1
            continue
        word = words[word_index]
        size = word_size(word)
        next_index = word_index
        while True:
            next_index += 1
            if next_index >= len(words):
                break
            else:
                next_word = words[next_index]
                if next_word in ["?", "!", ":"]:
                    word += " " + next_word
                    size += space_size + word_size(next_word)
                    to_skip += 1
                else:
                    break

        added_word = word
        added_size = size
        if not is_first_word:
            added_size += space_size
            added_word = " " + word
        if current_size + added_size <= max_width:
            current_line += added_word
            current_size += added_size
        else:
            final_text_list.append(current_line)
            final_size_list.append(current_size)
            current_line = word
            current_size = size
            continue
        is_first_word = False
    final_text_list.append(current_line)
    final_size_list.append(current_size)

for line in final_text_list:
    total = 0
    for c in line:
        total += width_dict[c]
    if total > max_width:
        print(f"ERROR: {line} ({total})")
        exit(2)

for size, line in zip(final_size_list, final_text_list):
    print(f"({size:>3}) {line}")

output_file = text_file.stem + "_" + header_path.with_suffix(".h").name
with open(output_file, "w") as f:
    _ = f.write(f"// Cut for a width of {max_width}\n")
    for line in final_text_list:
        _ = f.write(f'"{line}", //\n')
