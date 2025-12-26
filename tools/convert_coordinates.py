from argparse import ArgumentParser

def convert_coordinates(x: int, y: int, width: int, height: int) -> tuple[int, int]:
    """
    This function will convert values from Scratch's coordinate system to SDL's coordinate system.
    Scratch's coordinate system is a confusing mess that doesn't really make sense.
    While this should be technically correct, it isn't. Will need to debug later.
    """

    return (x + 240 - width // 2, 180 - y - height // 2)

if __name__ == "__main__":
    parser = ArgumentParser(description="Convert Scratch coordinates to SDL coordinates.")

    parser.add_argument("x", type=int, help="X coordinate in Scratch's coordinate system.")
    parser.add_argument("y", type=int, help="Y coordinate in Scratch's coordinate system.")
    parser.add_argument("width", type=int, help="Width of the sprite.")
    parser.add_argument("height", type=int, help="Height of the sprite.")

    x, y = convert_coordinates(**vars(parser.parse_args()))

    print(f"({x}, {y})")