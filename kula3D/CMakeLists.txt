cmake_minimum_required(VERSION 3.11)

project(kula3D)
execute_process(COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE PROJECT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

add_executable(${PROJECT_NAME} src/main.c src/utils.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fms-extensions -O2")

target_include_directories(${PROJECT_NAME} PRIVATE
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
)

execute_process(
  COMMAND magick
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/background.png -resize 144x80!
    \( ${CMAKE_CURRENT_SOURCE_DIR}/assets/kula.png -resize 60x60! \)
    -gravity center -composite ${CMAKE_CURRENT_BINARY_DIR}/icon0.png

  COMMAND magick
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/background.png -resize 480x272\! ${CMAKE_CURRENT_BINARY_DIR}/pic1.png
)

create_pbp_file(TARGET ${PROJECT_NAME}
  TITLE "Kula 3D"
  VERSION 01.00
  ICON_PATH ${CMAKE_CURRENT_BINARY_DIR}/icon0.png
  BACKGROUND_PATH ${CMAKE_CURRENT_BINARY_DIR}/pic1.png
)

set(DIST_DIRECTORY PSP/GAME/${PROJECT_NAME})
set(DIST_ARCHIVE ${PROJECT_NAME}-${PROJECT_VERSION}-psp.zip)

add_custom_target(${PROJECT_NAME}-dist ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIRECTORY}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${DIST_DIRECTORY}/assets
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/pic1.png ${DIST_DIRECTORY}/assets/background.png
  COMMAND magick ${DIST_DIRECTORY}/assets/kula.png -resize 25% ${DIST_DIRECTORY}/assets/kula.png
  COMMAND magick ${DIST_DIRECTORY}/assets/trekant2.png -resize 75% ${DIST_DIRECTORY}/assets/trekant2.png
  COMMAND ln -s ${DIST_DIRECTORY}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
  COMMAND ${CMAKE_COMMAND} -E copy EBOOT.PBP ${DIST_DIRECTORY}/EBOOT.PBP
  COMMAND ${CMAKE_COMMAND} -E tar c ${DIST_ARCHIVE} --format=zip ${DIST_DIRECTORY}
)