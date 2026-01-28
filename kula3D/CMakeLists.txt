cmake_minimum_required(VERSION 3.6)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define $VITASDK to point to your SDK path!")
  endif()
endif()

project(kula3D)
execute_process(COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE PROJECT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

include("${VITASDK}/share/vita.cmake" REQUIRED)

find_package(SDL2 REQUIRED PATHS "${VITASDK}/arm-vita-eabi/lib/cmake")
find_package(SDL2_image REQUIRED PATHS "${VITASDK}/arm-vita-eabi/lib/cmake")
find_package(SDL2_mixer REQUIRED PATHS "${VITASDK}/arm-vita-eabi/lib/cmake")
find_package(SDL2_ttf REQUIRED PATHS "${VITASDK}/arm-vita-eabi/lib/cmake")

set(VITA_APP_NAME "Kula 3D")
set(VITA_TITLEID  "KULA00003")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fms-extensions -O2")

add_executable(${PROJECT_NAME} src/main.c src/utils.c)
target_link_libraries(${PROJECT_NAME}
  SDL2_image SDL2_mixer SDL2_ttf SDL2::SDL2
  freetype
  jpeg png webp webpdemux
  FLAC mikmod modplug mpg123 opusfile opus vorbisfile vorbis ogg xmp-lite
  z bz2 stdc++ pthread
)

add_custom_target(sce_sys ALL
  COMMAND magick ${CMAKE_SOURCE_DIR}/assets/kula.png -resize 128x128\! PNG:- | pngquant - > ${CMAKE_CURRENT_BINARY_DIR}/icon0.png
  COMMAND magick ${CMAKE_SOURCE_DIR}/assets/background.png -resize 840x500\! PNG:- | pngquant - > ${CMAKE_CURRENT_BINARY_DIR}/bg.png
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}-${PROJECT_VERSION}-vita.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  NAME ${VITA_APP_NAME}
  FILE ${CMAKE_SOURCE_DIR}/assets assets
  FILE ${CMAKE_SOURCE_DIR}/template.xml sce_sys/livearea/contents/template.xml
  FILE ${CMAKE_CURRENT_BINARY_DIR}/bg.png sce_sys/livearea/contents/bg.png
# FILE ${CMAKE_CURRENT_BINARY_DIR}/startup.png sce_sys/livearea/contents/startup.png
  FILE ${CMAKE_CURRENT_BINARY_DIR}/icon0.png sce_sys/icon0.png
)