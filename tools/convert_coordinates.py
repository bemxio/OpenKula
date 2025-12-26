from argparse import ArgumentParser

def convert_coordinates(x: int, y: int, width: int, height: int) -> tuple[tuple[int, int], tuple[int, int]]:
    """
    This function will convert values from Scratch's coordinate system to SDL's coordinate system.
    I gotta be honest, Scratch's coordinate system is kind of confusing, to say the least.
    For whatever reason, Kula's origin seems to differ from the standard Scratch sprite origin by a little bit, requiring the use of silly offsets.
    Hence, two sets of coordinates are returned: one for normal use, and one specifically for the player sprite.
    I might just be the dumb one here, however this function does return an approximate position that works well enough.
    """

    return (
        (
            x + 240 - width // 2, 
            180 - y - height // 2
        ),
        (
            x + 240 - width + width // 4,
            180 - y - height // 2 + height // 4
        )
    )

if __name__ == "__main__":
    parser = ArgumentParser(description="Convert Scratch coordinates to SDL coordinates.")

    parser.add_argument("x", type=int, help="X coordinate in Scratch's coordinate system.")
    parser.add_argument("y", type=int, help="Y coordinate in Scratch's coordinate system.")
    parser.add_argument("width", type=int, help="Width of the sprite.")
    parser.add_argument("height", type=int, help="Height of the sprite.")

    (x1, y1), (x2, y2) = convert_coordinates(**vars(parser.parse_args()))

    print(f"Normal coordinates: ({x1}, {y1})")
    print(f"Kula coordinates: ({x2}, {y2})")