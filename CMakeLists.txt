cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "libcapture")
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
elseif(UNIX)
    # set(PROJECT_NAME "capture")
    list(
        APPEND
        SRC
        # ./src/linux/input/listener.c
        # ./src/linux/input/listener.h
        # ./src/linux/input/keyboard.c
        # ./src/linux/input/mouse.c
        ./src/linux/input/input.c
        ./src/linux/x11/utils.c
        # ./src/linux/input/keycode.c
        # ./src/linux/clipboard/clipboard.c
    )
else()
endif()

project(${PROJECT_NAME})

# 寻找 X11 库
find_package(X11 REQUIRED)

# 检查是否找到 X11 库
if(NOT X11_FOUND)
    message(FATAL_ERROR "X11 library not found")
endif()

# 添加 X11 头文件路径
include_directories(${X11_INCLUDE_DIR})
# target_link_libraries($(PROJECT_NAME))

# add_executable(${PROJECT_NAME} ${SRC})

add_library(${PROJECT_NAME} SHARED ${SRC})
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} Xtst Xinerama)
