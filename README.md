# OpenKula
A recreation of Kula, Kula 2 and Kula 3D from the [Kula Collection](https://store.steampowered.com/app/4237330/Kula_Collection/) by Mor10 Productions, written in C using [SDL](https://www.libsdl.org/). Aims to accurately replicate every nuance of the original Scratch projects, whilst allowing for portability across multiple platforms.

## Building
To build one of the game targets, follow steps for your target platform below.

### Linux
First, ensure you have the necessary dependencies installed. On Debian-based distributions, you can use the following command:
```sh
apt install build-essential git libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev python3
```
On Arch-based distributions, run:
```sh
pacman -S base-devel git python sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

Then, clone the repository and build the desired game:
```sh
git clone https://github.com/bemxio/OpenKula
cd OpenKula

make <kula|kula3D|kulatwo>
```
The built executable will be located inside the `build/` directory of your specified target. Alternatively, you can run the game using the `make <kula|kula3D|kulatwo> run` command.

### Windows (MinGW)
First, ensure you have the necessary dependencies installed. On Debian-based distributions, you can use the following command:
```sh
apt install build-essential mingw-w64 git libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev python3
```
On Arch-based distributions, run:
```sh
pacman -S base-devel mingw-w64-gcc git python sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

Then, clone the repository and build the desired game:
```sh
git clone https://github.com/bemxio/OpenKula
cd OpenKula

make WINDOWS=1 <kula|kula3D|kulatwo>
```
The built executable will be located inside the `build/` directory of your specified target. Alternatively, you can run the game using the `make WINDOWS=1 <kula|kula3D|kulatwo> run` command if you have [Wine](https://www.winehq.org/) installed.

## License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

Contributions are welcome! If you want to contribute in any way, whether it's an issue you've encountered or a pull request with new features, feel free to do so.