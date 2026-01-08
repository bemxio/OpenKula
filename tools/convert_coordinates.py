# pyright: reportOptionalOperand=false, reportOperatorIssue=false

import json
from argparse import ArgumentParser
from pathlib import Path

SCENE_WIDTH = 480
SCENE_HEIGHT = 360

def convert_coordinates(project: Path, sprite: str | None, x: int | None, y: int | None) -> None:
    """
    Alright, I think I got this figured out now. The rotational center of a sprite is stored inside the `project.json` file,
    and so, with that in mind, this function simply takes the sprite's position (either from the file or from the command line),
    and does some basic math to convert it to SDL coordinates. And also prints it out in YAML, for readability and funsies :-)
    """

    with open(project, "r", encoding="utf-8") as file:
        data = json.load(file)

    for target in data["targets"]:
        if target["isStage"]:
            continue

        if sprite is not None and target["name"] != sprite:
            continue

        print(f"{target['name']}:")

        for costume in target["costumes"]:
            print(f"{' ' * 2}- {costume['name']}:")

            rc_x = costume["rotationCenterX"]
            rc_y = costume["rotationCenterY"]

            if x is None or y is None:
                x, y = target["x"], target["y"]

            new_x = x + SCENE_WIDTH // 2 - rc_x
            new_y = SCENE_HEIGHT // 2 - y - rc_y

            print(f"{' ' * 6}Original coordinates: [{x}, {y}]")
            print(f"{' ' * 6}Rotation center: [{rc_x}, {rc_y}]")
            print(f"{' ' * 6}Converted coordinates: [{new_x}, {new_y}]")

if __name__ == "__main__":
    parser = ArgumentParser(description="Convert Scratch coordinates to SDL coordinates.")

    parser.add_argument("project", type=Path, help="Path to the Scratch's `project.json` file.")
    parser.add_argument("sprite", type=str, nargs="?", default=None, help="Name of the sprite to convert coordinates for. If not provided, all sprites will be processed.")
    parser.add_argument("x", type=int, nargs="?", default=None, help="X position of the sprite. Defaults to the value inside the project file.")
    parser.add_argument("y", type=int, nargs="?", default=None, help="Y position of the sprite. Defaults to the value inside the project file.")

    convert_coordinates(**vars(parser.parse_args()))