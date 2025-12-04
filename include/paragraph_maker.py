#!/usr/bin/env python3

import argparse
import re
from pathlib import Path
from re import Pattern


def wrap_text(
    header_path: Path,
    input_file: Path,
    max_width: int = 240,
    justify: bool = True,
    output_file: Path | None = None,
    show_output: bool = False,
) -> None:
    """Wrap a text under given constraints."""
    # === Creating character size map ===
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

    # === Splitting the text by lines ===
    def word_width(word: str) -> int:
        total = 0
        for letter in word:
            total += width_dict[letter]
        return total

    with open(input_file, "r", encoding="utf-8") as file:
        text_lines = [line.rstrip("\n") for line in file.readlines()]
    final_text_list_list: list[list[str]] = []
    final_width_list: list[int] = []
    final_justification_list: list[bool] = []
    space_width = width_dict[" "]
    for line in text_lines:
        current_line: list[str] = []
        current_width: int = 0
        is_first_word = True
        words = line.split(" ")
        to_skip = 0
        for word_index in range(len(words)):
            if to_skip > 0:
                to_skip -= 1
                continue
            word = words[word_index]
            width = word_width(word)
            next_index = word_index
            while True:  # Treat differently spaces before punctuation (for French)
                next_index += 1
                if next_index >= len(words):
                    break
                else:
                    next_word = words[next_index]
                    if next_word in ["?", "!", ":"]:
                        word += " " + next_word
                        width += space_width + word_width(next_word)
                        to_skip += 1
                    else:
                        break
            added_width = width
            if not is_first_word:
                added_width += space_width
            if current_width + added_width <= max_width:
                current_line += [word]
                current_width += added_width
            else:
                final_text_list_list.append(current_line)
                final_width_list.append(current_width)
                final_justification_list.append(True)
                current_line = [word]
                current_width = width
                continue
            is_first_word = False
        final_text_list_list.append(current_line)
        final_width_list.append(current_width)
        final_justification_list.append(False)

    # Create the final lines, justifying the text if needed
    final_text_list: list[str] = []
    if not justify:
        final_text_list = [" ".join(line) for line in final_text_list_list]
    else:
        final_width_list_justified: list[int] = []
        for width, line, justification in zip(
            final_width_list,
            final_text_list_list,
            final_justification_list,
        ):
            if not justification or len(line) == 1:
                final_text_list.append(" ".join(line))
                final_width_list_justified.append(width)
                continue
            nb_spaces: int = len(line) - 1
            # width_words is the width of the line without spaces
            width_words: int = width - nb_spaces * space_width
            width_available: int = max_width - width_words
            nb_space_between_words = width_available // (nb_spaces * space_width)

            # Now we have a fixed number of spaces between each word, but we can do
            # a bit better with adding an extra space between the first words:
            current_width = width_words + nb_space_between_words * space_width * nb_spaces
            left_width = max_width - current_width
            nb_extra = left_width // space_width  # the nb_extra first spaces can have one more character ! \o/
            reconstructed_line: str = line[0]
            for i in range(1, len(line)):
                word = line[i]
                space = " " * nb_space_between_words
                if i < nb_extra:
                    space += " "
                reconstructed_line += space + word

            final_width_list_justified.append(current_width + nb_extra * space_width)
            final_text_list.append(reconstructed_line)
        final_width_list = final_width_list_justified

    if show_output:
        for width, line, justification in zip(
            final_width_list,
            final_text_list,
            final_justification_list,
        ):
            print(f"({width:>3}) {'=' if justification else ' '} {line}")

    # Sanity check, it can fail if words are too big for the given size, like when one single word is too much
    for line in final_text_list:
        total = 0
        for c in line:
            total += width_dict[c]
        if total > max_width:
            print(f"ERROR: {line} ({total})")
            exit(1)

    if not output_file:
        output_file = Path(input_file.stem + "_" + header_path.with_suffix(".h").name)
    with open(output_file, "w", encoding="utf-8") as f:
        _ = f.write(f"// Cut for a width of {max_width}" + (" (justified)" if justify else "") + "\n")
        _ = f.write(f"// for font {header_path.name}\n\n")
        _ = f.write("constexpr const char *displayed_text[] =\n{")
        for line, width in zip(final_text_list, final_width_list):
            _ = f.write(f'"{line}", // ({width})\n')
        _ = f.write(f"}};\nconstexpr int text_width = {max_width};\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Wrap a text file according to constraints of size and character width.",
    )
    _ = parser.add_argument(
        "-l",
        "--length",
        type=int,
        help="max line length",
        default=240,
    )
    _ = parser.add_argument(
        "-j",
        "--justify",
        action="store_true",
        help="justify text by adding more space between words",
    )
    _ = parser.add_argument(
        "-f",
        "--font-header",
        type=Path,
        help="cpp header defining the font",
        required=True,
    )
    _ = parser.add_argument(
        "-i",
        "--input",
        type=Path,
        help="text file to convert",
        required=True,
    )
    _ = parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="optional path for exported text",
    )
    _ = parser.add_argument(
        "-s",
        "--show",
        action="store_true",
        help="show in console the exported text, line size and justification",
    )
    args = parser.parse_args()

    if not Path(args.input).exists():
        print(f"ERROR: input file {args.input} doesn't exist.")
        exit(1)
    if not Path(args.font_header).exists():
        print(f"ERROR: font header {args.font_header} doesn't exist.")
        exit(1)

    wrap_text(
        header_path=args.font_header,
        input_file=args.input,
        max_width=args.length,
        justify=args.justify,
        output_file=args.output,
        show_output=args.show,
    )
