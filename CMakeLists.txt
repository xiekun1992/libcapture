cmake_minimum_required(VERSION 3.22)

project(libcapture)

set(
  SRC
  ./src/input/listener.c
  # ./src/clipboard/clipboard.c
  ./src/utils.c
)

# target_link_libraries($(PROJECT_NAME))

# add_executable(${PROJECT_NAME} ${SRC})

add_library(${PROJECT_NAME} SHARED ${SRC})