cmake_minimum_required(VERSION 3.17)
project(chess2)

set(CMAKE_C_STANDARD 11)

#set(MAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.c)

include_directories(
        ${PROJECT_SOURCE_DIR}/dependencies/GLFW/include
        ${PROJECT_SOURCE_DIR}/dependencies/GLEW/include
        ${PROJECT_SOURCE_DIR}/dependencies/imgui/include
        )

link_directories(
        ${PROJECT_SOURCE_DIR}/dependencies/GLFW/lib
        ${PROJECT_SOURCE_DIR}/dependencies/GLEW/lib
        )

add_executable(chess2 ${SOURCE_FILES}
        src/app.cpp
        src/filem.c
        src/filem.h
        src/main.c
        src/tempiece.c
        src/tempiece.h
        src/game.c
        src/game.h
        src/imgui/imconfig.h
        src/imgui/imgui.h
        src/imgui/imgui.cpp
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_impl_glfw.h
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui_impl_opengl3.h
        src/imgui/imgui_impl_opengl3.cpp
        src/imgui/imgui_internal.h
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imstb_rectpack.h
        src/imgui/imstb_textedit.h
        src/imgui/imstb_truetype.h
        )

target_link_libraries(chess2 glfw3 glew32 opengl32 libSDL2)
