# OpenKula
A recreation of Kula, Kula 2 and Kula 3D from the [Kula Collection](https://store.steampowered.com/app/4237330/Kula_Collection/) by Mor10 Productions, written in C using [SDL2](https://www.libsdl.org/). Aims to accurately replicate every nuance of the original Scratch projects, whilst allowing for portability across multiple platforms.

## Supported platforms
OpenKula has been ported to and tested on various platforms, with varying levels of playability:

- PC (Windows, Linux, BSD etc.)
- [Nintendo Wii](https://github.com/bemxio/OpenKula/tree/wii) (minor performance issues)
- [PlayStation 3](https://github.com/bemxio/OpenKula/tree/ps3) (unplayable, crashes on real hardware)
- [PlayStation Portable](https://github.com/bemxio/OpenKula/tree/psp) (text rendering issues)
- [PlayStation Vita](https://github.com/bemxio/OpenKula/tree/vita)
- [Xbox](https://github.com/bemxio/OpenKula/tree/xbox) (major performance issues)

<!--
My goal is to port OpenKula to all consoles and I (or my friends) own, and so here's a list of potential future platforms:

- Nintendo DS (SDL1)
- Nintendo 3DS
- PlayStation 2
- PlayStation 3 (SDL1)
- Sega Dreamcast (SDL1)
- Xbox (SDL1/RXDK)
- Xbox 360 (SDL1)
- Xbox One/Series X/S

Some do require an SDL1 backport, and if I really feel dedicated to this, a full migration from SDL to the platform's SDK.
-->

## Building
To build one of the game targets, follow steps for your target platform below.

### Prerequisites
Before building, ensure you have the following dependencies installed:

- [GCC](https://gcc.gnu.org/) 9.x+ or [Clang](https://clang.llvm.org/) (GCC is used by default, Clang can be used by setting the `CC` environment variable)
- [SDL2](https://www.libsdl.org/) with [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/), and [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [Python](https://www.python.org/) 3.6+ with [CairoSVG](https://cairosvg.org/)
- [GNU Make](https://www.gnu.org/software/make/)
- [Git](https://git-scm.com/)
- (Optional) [MinGW-w64](https://www.mingw-w64.org/) for cross-compiling to Windows

On Debian-based distributions, you can install everything you need with `apt install build-essential git libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev python3 python3-cairosvg`.
On Arch-based distros, use `pacman -S base-devel git sdl2 sdl2_image sdl2_mixer sdl2_ttf python python-cairosvg`.

### Assets
For copyright reasons, you'll need to provide the game assets yourself by copying them from your legally obtained Kula Collection installation. The required files are located in the `<kula|kula3D|kulatwo>/resources/app/assets/` directory inside Kula Collection's root directory.

Simply clone the repository, then copy the assets into the `assets/` directory:

```bash
git clone https://github.com/bemxio/OpenKula
cd OpenKula

cp -r ~/.steam/steam/steamapps/common/Kula\ Collection/*/resources/app/assets/*.{svg,mp3} assets/ # Adjust the source path as necessary
```

### Compilation
After installing all dependencies and copying assets, build the desired target with `make`:

```bash
# Unix-like systems (Linux, BSD, etc.)
make <kula|kula3D|kulatwo> # Replace <kula|kula3D|kulatwo> with your desired target

# Windows (using MinGW)
make WINDOWS=1 <kula|kula3D|kulatwo> # Replace <kula|kula3D|kulatwo> with your desired target
```

This will produce an executable file together with the assets inside the `build/<kula|kula3D|kulatwo>` directory. You can also run `make <kula|kula3D|kulatwo> run` to immediately launch the game after building, or `make` to build all three targets at once.

In case of cross-compiling for Windows, you can also bundle the required DLLs and package everything into a ZIP file with `make WINDOWS=1 <kula|kula3D|kulatwo> dist`.

## License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

Contributions are welcome! If you want to contribute in any way, whether it's an issue you've encountered or a pull request with new features, feel free to do so.