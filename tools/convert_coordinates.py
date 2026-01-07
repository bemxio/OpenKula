import json
from argparse import ArgumentParser
from pathlib import Path

WIDTH = 480
HEIGHT = 360

def convert_coordinates(project: Path, sprite: str, x: int, y: int) -> None:
    with open(project, "r", encoding="utf-8") as file:
        data = json.load(file)

    rc_x, rc_y = 0, 0

    for target in data["targets"]:
        for costume in target["costumes"]:
            if not costume["name"] == sprite:
                continue

            rc_x = costume["rotationCenterX"]
            rc_y = costume["rotationCenterY"]

            break

    new_x = x + WIDTH // 2 - rc_x
    new_y = HEIGHT // 2 - y - rc_y

    print(f"Original coordinates: ({x}, {y})")
    print(f"Rotation center: ({rc_x}, {rc_y})")
    print(f"Converted coordinates: ({new_x}, {new_y})")

if __name__ == "__main__":
    parser = ArgumentParser(description="Convert Scratch coordinates to SDL coordinates.")

    parser.add_argument("project", type=Path, help="Path to the Scratch's project.json file.")
    parser.add_argument("sprite", type=str, help="Name of the sprite to convert coordinates for.")
    parser.add_argument("x", type=int, help="X position in Scratch's coordinate system.")
    parser.add_argument("y", type=int, help="Y position in Scratch's coordinate system.")

    convert_coordinates(**vars(parser.parse_args()))