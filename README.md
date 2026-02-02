# OpenKula
A recreation of Kula, Kula 2 and Kula 3D from the [Kula Collection](https://store.steampowered.com/app/4237330/Kula_Collection/) by Mor10 Productions, written in C using [SDL](https://www.libsdl.org/). Aims to accurately replicate every nuance of the original Scratch projects, whilst allowing for portability across multiple platforms.

## Supported platforms
OpenKula has been ported to and tested on the following platforms:
- [PC (Windows, Linux, BSD etc.)](https://github.com/bemxio/OpenKula/tree/main)
- Nintendo Wii
- [PlayStation Portable](https://github.com/bemxio/OpenKula/tree/psp)
- [PlayStation Vita](https://github.com/bemxio/OpenKula/tree/vita)
- [Xbox](https://github.com/bemxio/OpenKula/tree/xbox)

## Building
To build one of the game targets, follow steps for your target platform below.

### Prerequisites
Before building, ensure you have the following dependencies installed:
- [devkitARM](https://github.com/devkitpro/) with the `wii-dev` metapackage
- [SDL2](https://www.libsdl.org/) with [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/), and [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [Python](https://www.python.org/) 3.6+ with [CairoSVG](https://cairosvg.org/)
- [ImageMagick](https://imagemagick.org/) 7+
- [CMake](https://cmake.org/) 3.13+
- [GNU Make](https://www.gnu.org/software/make/)
- [Git](https://git-scm.com/)

After installing/configuring `pacman` with devkitPro's repositories, you can get everything you need with `(dkp-)pacman -S git make cmake libfat-ogc python python-cairosvg wii-cmake wii-dev wii-sdl2 wii-sdl2_image wii-sdl2_mixer wii-sdl2_ttf`.

### Assets
For copyright reasons, you'll need to provide the game assets yourself by copying them from your legally obtained Kula Collection installation. The required files are located in the `<kula|kula3D|kulatwo>/resources/app/assets/` directory inside Kula Collection's root directory.

Simply clone the repository, then copy the assets into the `assets/` directory:
Simply clone the repository, then copy the assets into the `assets/` directory:
```bash
git clone https://github.com/bemxio/OpenKula
cd OpenKula

cp -r ~/.steam/steam/steamapps/common/Kula\ Collection/*/resources/app/assets/*.{svg,mp3} assets/ # Adjust the source path as necessary
```

### Compilation
After installing all dependencies and copying assets, build the desired target with `make`:
```bash
make <kula|kula3D|kulatwo> # Replace <kula|kula3D|kulatwo> with your desired target
```

This will produce an `apps` directory with the necessary files in the `build/<kula|kula3D|kulatwo>/` directory. You can also run `make` to build all three targets at once.

## License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

Contributions are welcome! If you want to contribute in any way, whether it's an issue you've encountered or a pull request with new features, feel free to do so.