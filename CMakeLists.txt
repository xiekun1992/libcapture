cmake_minimum_required(VERSION 3.22)

project(libcapture)

set(
  SRC
  ./src/input/listener.c
  ./src/input/keyboard.c
  ./src/input/mouse.c
  ./src/input/helper.c
  ./src/clipboard/clipboard.c
  ./src/utils.c
  ./src/service/service.c
)

# target_link_libraries($(PROJECT_NAME))

# add_executable(${PROJECT_NAME} ${SRC})

add_library(${PROJECT_NAME} SHARED ${SRC})
