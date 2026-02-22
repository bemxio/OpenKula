cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DEVKITPRO})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DEVKITPRO}/cmake/3DS.cmake" CACHE PATH "toolchain file")
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

add_subdirectory(../submodules/SDL ${CMAKE_BINARY_DIR}/SDL)
add_subdirectory(../submodules/SDL_image ${CMAKE_BINARY_DIR}/SDL_image)
add_subdirectory(../submodules/SDL_mixer ${CMAKE_BINARY_DIR}/SDL_mixer)
add_subdirectory(../submodules/SDL_ttf ${CMAKE_BINARY_DIR}/SDL_ttf)

include_directories(
  ../submodules/SDL/include
  ../submodules/SDL_image/include
  ../submodules/SDL_mixer/include
  ../submodules/SDL_ttf/include
)
link_directories(
  ${CMAKE_BINARY_DIR}/SDL
  ${CMAKE_BINARY_DIR}/SDL_image
  ${CMAKE_BINARY_DIR}/SDL_mixer
  ${CMAKE_BINARY_DIR}/SDL_ttf
)

add_executable(${PROJECT_NAME} src/main.c src/utils.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fms-extensions -O2")

target_link_libraries(${PROJECT_NAME}
  SDL2_image SDL2_mixer SDL2_ttf
  SDL2 SDL2main
  freetype png
  z bz2 stdc++
)