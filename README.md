# OpenKula
A recreation of Kula, Kula 2 and Kula 3D from the [Kula Collection](https://store.steampowered.com/app/4237330/Kula_Collection/) by Mor10 Productions, written in C using [SDL2](https://www.libsdl.org/). Aims to accurately replicate every nuance of the original Scratch projects, whilst allowing for portability across multiple platforms.

## Supported platforms
OpenKula has been ported to and tested on various platforms, with varying levels of playability:

- [PC (Windows, Linux, BSD etc.)](https://github.com/bemxio/OpenKula/tree/main)
- [Nintendo Wii](https://github.com/bemxio/OpenKula/tree/wii) (minor performance issues)
- [PlayStation 3](https://github.com/bemxio/OpenKula/tree/ps3) (unplayable, crashes on real hardware)
- [PlayStation Portable](https://github.com/bemxio/OpenKula/tree/psp) (text rendering issues)
- [PlayStation Vita](https://github.com/bemxio/OpenKula/tree/vita)
- Xbox (major performance issues)

## Building
To build one of the game targets, follow steps for your target platform below.

### Prerequisites
Before building, ensure you have the following dependencies installed:

- [Clang](https://clang.llvm.org/)
- [GNU Bison](https://www.gnu.org/software/bison/) and [flex](https://github.com/westes/flex)
- [LLD](https://lld.llvm.org/)
- [Python](https://www.python.org/) 3.6+ with [CairoSVG](https://cairosvg.org/)
- [FFmpeg](https://ffmpeg.org/)
- [GNU Make](https://www.gnu.org/software/make/)
- [Git](https://git-scm.com/)

On Debian-based distributions, you can install everything you need with `apt install bison clang ffmpeg flex git lld make python3 python3-cairosvg`.
On Arch-based distros, use `pacman -S bison clang ffmpeg flex git lld make python python-cairosvg`.

### Assets
For copyright reasons, you'll need to provide the game assets yourself by copying them from your legally obtained Kula Collection installation. The required files are located in the `<kula|kula3D|kulatwo>/resources/app/assets/` directory inside Kula Collection's root directory.

Simply clone the repository with the `--recurse-submodules` flag, then copy the assets into the `assets/` directory:

```bash
git clone --recurse-submodules https://github.com/bemxio/OpenKula
cd OpenKula

cp -r ~/.steam/steam/steamapps/common/Kula\ Collection/*/resources/app/assets/*.{svg,mp3} assets/ # Adjust the source path as necessary
```

### Compilation
After installing all dependencies, cloning the repository and copying assets, source the `activate_nxdk.sh` script and build the desired target with `make`:

```bash
source activate_nxdk.sh
make <kula|kula3D|kulatwo> # Replace <kula|kula3D|kulatwo> with your desired target
```

This will produce an ISO image inside the `src/<kula|kula3D|kulatwo>` directory. You can also run `make` to build all three targets at once.

## License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

Contributions are welcome! If you want to contribute in any way, whether it's an issue you've encountered or a pull request with new features, feel free to do so.