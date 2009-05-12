
include_directories (.)
include_directories (../src)
include_directories(include ${SDL_INCLUDE_DIR})
include_directories(include ${SDL_TTF_INCLUDE_DIR})
include_directories(include ${SDL_IMAGE_INCLUDE_DIR})

add_definitions(`sdl-config --cflags`)

link_libraries(gameui ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY})

add_executable(gameuitest 
  events.cpp netwalkwindow.cpp gameuitest.cpp
)

