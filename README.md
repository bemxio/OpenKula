# OpenKula
A recreation of Kula, Kula 2 and Kula 3D from the [Kula Collection](https://store.steampowered.com/app/4237330/Kula_Collection/) by Mor10 Productions, written in C using [SDL2](https://www.libsdl.org/). Aims to accurately replicate every nuance of the original Scratch projects, whilst allowing for portability across multiple platforms.

## Supported platforms
OpenKula has been ported to and tested on various platforms, with varying levels of playability:

- [PC (Windows, Linux, BSD etc.)](https://github.com/bemxio/OpenKula/tree/main)
- [Nintendo Wii](https://github.com/bemxio/OpenKula/tree/wii) (minor performance issues)
- PlayStation 3 (unplayable, crashes on real hardware)
- [PlayStation Portable](https://github.com/bemxio/OpenKula/tree/psp) (text rendering issues)
- [PlayStation Vita](https://github.com/bemxio/OpenKula/tree/vita)
- [Xbox](https://github.com/bemxio/OpenKula/tree/xbox) (major performance issues)

## Building
To build one of the game targets, follow steps for your target platform below.

### Prerequisites
The easiest way to set up a build environment is to use [Docker](https://www.docker.com/) and the bundled-in [`Dockerfile`](Dockerfile) that will create an image with all the necessary tools pre-installed. You'll also need [Git](https://git-scm.com/) to clone the repository.

On Arch-based Linux distributions, you can install both of those with `pacman -S docker git`. On other distros, refer to Docker's official website and your package manager for instructions.

<!-- For the Docker haters out there, I'm sorry, but it's either that, a Debian 12 chroot/VM or creating an updated fork of PSL1GHT, and I ain't got the energy to do that :-) 
If you REALLY want to do this without Docker, set up a Debian 12 environment, install https://github.com/ps3dev/ps3toolchain, github.com/humbertodias/SDL2_PSL1GHT_Libs, `python3-cairosvg` and `imagemagick`, then run `make <kula|kula3D|kulatwo>`. -->

### Assets
For copyright reasons, you'll need to provide the game assets yourself by copying them from your legally obtained Kula Collection installation. The required files are located in the `<kula|kula3D|kulatwo>/resources/app/assets/` directory inside Kula Collection's root directory.

Simply clone the repository, then copy the assets into the `assets/` directory:

```bash
git clone https://github.com/bemxio/OpenKula
cd OpenKula

cp -r ~/.steam/steam/steamapps/common/Kula\ Collection/*/resources/app/assets/*.{svg,mp3} assets/ # Adjust the source path as necessary
```

### Container setup
To build the Docker image, run the following command in the root of the repository:

```bash
docker build -t openkula .
```

This will create a Debian 12-based image with the necessary dependencies, including [PSL1GHT](https://psl1ght.com/), [SDL2_PSL1GHT](https://github.com/humbertodias/SDL2_PSL1GHT/) with its libraries and [CairoSVG](https://cairosvg.org/).

### Compilation
After installing all dependencies and copying assets, build the desired target with `make`:

```bash
docker run --rm -v "$(pwd)":/OpenKula -w /OpenKula openkula make <kula|kula3D|kulatwo> # Replace <kula|kula3D|kulatwo> with your desired target
```

This will produce a `<kula|kula3D|kulatwo>.gnpdrm.pkg` file inside the `<kula|kula3D|kulatwo>` directory. You can also run `make` to build all three targets at once.

## License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

Contributions are welcome! If you want to contribute in any way, whether it's an issue you've encountered or a pull request with new features, feel free to do so.