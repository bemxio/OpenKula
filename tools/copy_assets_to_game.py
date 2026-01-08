import argparse
import base64
import os
import shutil
import xml.etree.ElementTree as ET

LOOKUP_TABLE = {
    "kula": {
        "aeaf1f511fa2bef67371ed62528686df.svg": "fiende01.png",
        "5fc0d3bc8029acfb10700893fc7b7733.svg": "fiende02.png",
        "8a9336e1b924b53fb0d70634706a3392.svg": "kula.png",
        "2fe2f71497a79460dd88fb83987c29b6.svg": "kulabakgrunn.png",
        "077b5dbb78e1bc63ae11b483d3f5b20f.mp3": "mortietunes.mp3",
        "skrifttype.ttf": "skrifttype.ttf"
    },
    "kula3D": {
        "2dbac4b426800a196082eb5b7c3a7538.svg": "fiende01.png",
        "cd58cacba669ecd6177243b1cfbeaf34.svg": "fiende02.png",
        "d06adeb3a40b10f666861146e668179c.svg": "kula.png",
        "3dfdfd9f379a15b83ff175401117592d.svg": "kulabakgrunn.png",
        "077b5dbb78e1bc63ae11b483d3f5b20f.mp3": "mortietunes.mp3",
        "skrifttype.ttf": "skrifttype.ttf"
    },
    "kulatwo": {}
}

def extract_png_from_svg(source: str, target: str) -> None:
    tree = ET.parse(source)
    root = tree.getroot()

    image = root[0][0][0] # lol
    data = image.attrib["{http://www.w3.org/1999/xlink}href"]

    data = data.split(",")[1]
    data = base64.b64decode(data)

    with open(target, "wb") as file:
        file.write(data)

def copy_assets_to_game(game: str, directory: str) -> None:
    os.chdir(directory)

    if not os.path.exists(f"{game}/assets"):
        os.mkdir(f"{game}/assets")

    for source, target in LOOKUP_TABLE[game].items():
        #print(f"{source} -> {target}")

        if source.endswith(".svg"):
            extract_png_from_svg(f"assets/{source}", f"{game}/assets/{target}")
        else:
            shutil.copy2(f"assets/{source}", f"{game}/assets/{target}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Copy asset files to a specified OpenKula game directory, extracting PNGs from SVGs.")

    parser.add_argument("game", type=str, choices=LOOKUP_TABLE.keys(), help="The game to copy assets for.")
    parser.add_argument("--directory", "-d", type=str, default=".", help="The OpenKula directory with the game directories. Defaults to the current directory.")

    copy_assets_to_game(**vars(parser.parse_args()))