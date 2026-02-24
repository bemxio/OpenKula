# OpenKula
A recreation of Kula, Kula 2 and Kula 3D from the [Kula Collection](https://store.steampowered.com/app/4237330/Kula_Collection/) by Mor10 Productions, written in C using [SDL2](https://www.libsdl.org/). Aims to accurately replicate every nuance of the original Scratch projects, whilst allowing for portability across multiple platforms.

## Supported platforms
OpenKula has been ported to and tested on various platforms, with varying levels of playability:

- PC (Windows, Linux, BSD etc.)
- [Nintendo 3DS](https://github.com/bemxio/OpenKula/tree/3ds) (major performance issues)
- [Nintendo Wii](https://github.com/bemxio/OpenKula/tree/wii)
- [PlayStation 3](https://github.com/bemxio/OpenKula/tree/ps3) (unplayable, crashes on real hardware)
- [PlayStation Portable](https://github.com/bemxio/OpenKula/tree/psp) (text rendering issues)
- [PlayStation Vita](https://github.com/bemxio/OpenKula/tree/vita)
- [Xbox](https://github.com/bemxio/OpenKula/tree/xbox) (major performance issues)

## Building
To build one of the game targets, follow steps for your target platform below.

### Prerequisites
Before building, ensure you have the following dependencies installed:

- [devkitPro](https://github.com/devkitpro/) with the `3ds-dev` metapackage
- `3ds-cmake`, `3ds-libmodplug`, `3ds-libxmp` and `3ds-opusfile`
- [Python](https://www.python.org/) 3.6+ with [CairoSVG](https://cairosvg.org/)
- [ImageMagick](https://imagemagick.org/) 7+
- [CMake](https://cmake.org/) 3.13+
- [GNU Make](https://www.gnu.org/software/make/)
- [Git](https://git-scm.com/)

After installing/configuring `pacman` with devkitPro's repositories, you can get everything you need with `(dkp-)pacman -S git make cmake python python-cairosvg 3ds-cmake 3ds-dev 3ds-libmodplug 3ds-libxmp 3ds-opusfile`.

### Assets
For copyright reasons, you'll need to provide the game assets yourself by copying them from your legally obtained Kula Collection installation. The required files are located in the `<kula|kula3D|kulatwo>/resources/app/assets/` directory inside Kula Collection's root directory.

Simply clone the repository with the `--recurse-submodules` flag, then copy the assets into the `assets/` directory:

```bash
git clone --recurse-submodules https://github.com/bemxio/OpenKula
cd OpenKula

cp -r ~/.steam/steam/steamapps/common/Kula\ Collection/*/resources/app/assets/*.{svg,mp3} assets/ # Adjust the source path as necessary
```

### Compilation
After installing all dependencies and copying assets, build the desired target with `make`:

```bash
make <kula|kula3D|kulatwo> # Replace <kula|kula3D|kulatwo> with your desired target
```

This will produce a 3DSX package inside the `build/<kula|kula3D|kulatwo>` directory. You can also run `make` to build all three targets at once.

## License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

Contributions are welcome! If you want to contribute in any way, whether it's an issue you've encountered or a pull request with new features, feel free to do so.