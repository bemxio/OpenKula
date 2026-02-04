FROM debian:12-slim
WORKDIR /build

# environment variables
ENV PS3DEV /usr/local/ps3dev
ENV PSL1GHT "${PS3DEV}"
ENV PATH "${PATH}:${PS3DEV}/bin:${PS3DEV}/ppu/bin:${PS3DEV}/spu/bin"

# install dependencies
RUN apt update && apt upgrade -y && \
    apt install -y autoconf automake bison bzip2 clang flex g++ gcc git \
        libelf-dev libgmp3-dev libncurses5-dev libssl-dev libtool libtool-bin make \
        patch pkg-config python-is-python3 python-dev-is-python3 subversion texinfo wget xz-utils zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

# build and install ps3toolchain
RUN git clone https://github.com/bemxio/ps3toolchain && \
    cd ps3toolchain && \
    ./toolchain.sh && \
    rm -rf ps3toolchain

# build and install SDL1, SDL2 and their libs for PSL1GHT
run git clone https://github.com/humbertodias/SDL2_PSL1GHT_Libs && \
    cd SDL2_PSL1GHT_Libs && \
    ./sdl_psl1ght.sh && ./sdl2_psl1ght.sh && \
    ./make_SDL_Libs.sh && \
    rm -rf SDL2_PSL1GHT_Libs