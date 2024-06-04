cmake_minimum_required(VERSION 3.22)
project(libcapture)

set(SRC)
if (CMAKE_SYSTEM_NAME MATCHES "Windows") 
    list(
        APPEND
        SRC
        ./src/windows/input/listener.c
        ./src/windows/input/keyboard.c
        ./src/windows/input/mouse.c
        ./src/windows/input/helper.c
        ./src/windows/clipboard/clipboard.c
        ./src/windows/utils.c
        ./src/windows/service/service.c
    )
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(
        APPEND
        SRC
        ./src/linux/input/listener.c
        ./src/linux/input/keyboard.c
        ./src/linux/input/mouse.c
        ./src/linux/input/helper.c
        ./src/linux/clipboard/clipboard.c
        ./src/linux/utils.c
        ./src/linux/service/service.c
    )
else()
endif()
# target_link_libraries($(PROJECT_NAME))

# add_executable(${PROJECT_NAME} ${SRC})

add_library(${PROJECT_NAME} SHARED ${SRC})
