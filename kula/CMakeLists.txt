cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DEVKITPRO})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DEVKITPRO}/cmake/Wii.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define $DEVKITPRO to point to your toolchain path!")
  endif()
endif()

project(kula)
execute_process(COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE PROJECT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/meta.xml ${CMAKE_CURRENT_BINARY_DIR}/meta.xml)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fms-extensions -O2")

add_executable(${PROJECT_NAME}
  src/main.c src/utils.c
)
target_link_libraries(${PROJECT_NAME}
  SDL2_image SDL2_mixer SDL2_ttf
  SDL2::SDL2 SDL2main
  freetype harfbuzz
  png
  modplug opusfile opus ogg
  z bz2
  stdc++
)

ogc_create_dol(${PROJECT_NAME})

set(DIST_DIRECTORY apps/${PROJECT_NAME})
set(DIST_ARCHIVE ${PROJECT_NAME}-${PROJECT_VERSION}-wii.zip)

add_custom_target(dist ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIRECTORY}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${DIST_DIRECTORY}/assets
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dol ${DIST_DIRECTORY}/boot.dol
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/meta.xml ${DIST_DIRECTORY}
# COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/icon.png ${DIST_DIRECTORY}
  COMMAND ${CMAKE_COMMAND} -E tar c ${DIST_ARCHIVE} --format=zip ${DIST_DIRECTORY}
)