cmake_minimum_required(VERSION 2.6)
project(GameUI)

set(CMAKE_MODULE_PATH "${GameUI_SOURCE_DIR}/cmake-modules")
include(${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)

# Do Configure checks.
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
#find_package(LibSigCXX2 REQUIRED )
find_package(Iconv)

check_include_file("errno.h" HAVE_ERRNO_H)


#if( NOT LIBSIGCXX2_FOUND )
#  message( SEND_ERROR "Failed to find the required package 'libsigc+ +' )
#endif( NOT LIBSIGCXX2_FOUND )

if(ICONV_IS_CONST)
  set(ICONV_CONST "const")
else(ICONV_IS_CONST)
  set(ICONV_CONST "")
endif(ICONV_IS_CONST)

IF(NOT SDL_FOUND)
  message(SEND_ERROR "!!! SDL not found.")
ENDIF(NOT SDL_FOUND)

IF(NOT SDLTTF_FOUND)
  message(SEND_ERROR "!!! SDL_ttf not found.")
ENDIF(NOT SDLTTF_FOUND)

IF(NOT SDLIMAGE_FOUND)
  message(SEND_ERROR "!!! SDL_image not found.")
ENDIF(NOT SDLIMAGE_FOUND)

# This should be done in a better way.
set(VERSION "0.2.1")

configure_file(config.h.in src/config.h)
configure_file(config.h.in test/config.h)

add_subdirectory(src)
add_subdirectory(test)

