cmake_minimum_required(VERSION 3.17)
project(chess2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(blah
        dependencies/blah/src/core/app.cpp
        dependencies/blah/src/core/filesystem.cpp
        dependencies/blah/src/core/common.cpp
        dependencies/blah/src/core/time.cpp

        dependencies/blah/src/graphics/batch.cpp
        dependencies/blah/src/graphics/blend.cpp
        dependencies/blah/src/graphics/framebuffer.cpp
        dependencies/blah/src/graphics/material.cpp
        dependencies/blah/src/graphics/mesh.cpp
        dependencies/blah/src/graphics/renderpass.cpp
        dependencies/blah/src/graphics/shader.cpp
        dependencies/blah/src/graphics/spritefont.cpp
        dependencies/blah/src/graphics/subtexture.cpp
        dependencies/blah/src/graphics/texture.cpp

        dependencies/blah/src/input/input.cpp
        dependencies/blah/src/input/binding.cpp
        dependencies/blah/src/input/binding_registry.cpp

        dependencies/blah/src/containers/str.cpp

        dependencies/blah/src/images/aseprite.cpp
        dependencies/blah/src/images/font.cpp
        dependencies/blah/src/images/image.cpp
        dependencies/blah/src/images/packer.cpp

        dependencies/blah/src/math/calc.cpp
        dependencies/blah/src/math/circle.cpp
        dependencies/blah/src/math/color.cpp
        dependencies/blah/src/math/line.cpp
        dependencies/blah/src/math/mat3x2.cpp
        dependencies/blah/src/math/mat4x4.cpp
        dependencies/blah/src/math/point.cpp
        dependencies/blah/src/math/quad.cpp
        dependencies/blah/src/math/rect.cpp
        dependencies/blah/src/math/rectI.cpp
        dependencies/blah/src/math/stopwatch.cpp
        dependencies/blah/src/math/vec2.cpp

        dependencies/blah/src/streams/bufferstream.cpp
        dependencies/blah/src/streams/filestream.cpp
        dependencies/blah/src/streams/memorystream.cpp
        dependencies/blah/src/streams/stream.cpp

        dependencies/blah/src/internal/graphics_backend_gl.cpp
        dependencies/blah/src/internal/graphics_backend_d3d11.cpp
        dependencies/blah/src/internal/graphics_backend_dummy.cpp
        dependencies/blah/src/internal/platform_backend_sdl2.cpp
        dependencies/blah/src/internal/platform_backend_win32.cpp
        )

target_include_directories(blah
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

set(PLATFORM_SDL2 true CACHE BOOL "Use SDL2 Platform Backend")
set(PLATFORM_WIN32 false CACHE BOOL "Use Win32 Platform Backend")
set(GRAPHICS_OPENGL true CACHE BOOL "Use OpenGL Graphics Backend")
set(GRAPHICS_D3D11 false CACHE BOOL "Use D3D11 Graphics Backend")

set(LIBS "")

# use the OpenGL Graphics Backend
if (GRAPHICS_OPENGL)

        add_compile_definitions(BLAH_GRAPHICS_OPENGL)

        # use the D3D11 Graphics Backend
elseif (GRAPHICS_D3D11)

        add_compile_definitions(BLAH_GRAPHICS_D3D11)
        set(LIBS ${LIBS} d3d11.lib dxguid.lib D3Dcompiler.lib)

endif()

# use the SDL2 Platform Backend
# Link and create SDL2 Definition
if (PLATFORM_SDL2)
        add_compile_definitions(BLAH_PLATFORM_SDL2)

        # Emscripten can import SDL2 directly
        if (EMSCRIPTEN)

                set_target_properties(blah PROPERTIES COMPILE_FLAGS "-s USE_SDL=2")

                # Load SDL2 Normally
        else()

                # Try to find SDL2
                if (DEFINED SDL2_LIBRARIES AND DEFINED SDL2_INCLUDE_DIRS)
                        set(SDL2_FOUND true)
                else()
                        find_package(SDL2 QUIET)
                endif()

                # If CMake cannot find SDL2 library, then it gets downloaded and compiled that way
                if (NOT ${SDL2_FOUND})

                        include(FetchContent)
                        FetchContent_Declare(
                                SDL2
                                GIT_REPOSITORY https://github.com/libsdl-org/SDL
                                GIT_TAG release-2.0.14 # grab latest stable release
                        )
                        FetchContent_GetProperties(SDL2)
                        if (NOT sdl2_POPULATED)
                                FetchContent_Populate(SDL2)
                                add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
                        endif()

                endif()

                # Add Library and Include Dirs
                set(LIBS ${LIBS} ${SDL2_LIBRARIES})
                target_include_directories(blah PUBLIC ${SDL2_INCLUDE_DIRS})

        endif()

        # use the Win32 Platform Backend
elseif (PLATFORM_WIN32)

        add_compile_definitions(BLAH_PLATFORM_WIN32)

endif()

include_directories(${PROJECT_SOURCE_DIR}/dependencies/blah/include)

add_executable(chess2 ${SOURCE_FILES}
        src/filem.c
        src/filem.h
        src/main.c
        src/piece.c
        src/piece.h
        src/game.c
        src/game.h
        src/app.cpp

        src/gui/sprite.cpp
        src/gui/sprite.h
        src/gui/GuiButton.cpp
        src/gui/GuiButton.h

        dependencies/blah/src/core/app.cpp
        dependencies/blah/src/core/filesystem.cpp
        dependencies/blah/src/core/common.cpp
        dependencies/blah/src/core/time.cpp

        dependencies/blah/src/graphics/batch.cpp
        dependencies/blah/src/graphics/blend.cpp
        dependencies/blah/src/graphics/framebuffer.cpp
        dependencies/blah/src/graphics/material.cpp
        dependencies/blah/src/graphics/mesh.cpp
        dependencies/blah/src/graphics/renderpass.cpp
        dependencies/blah/src/graphics/shader.cpp
        dependencies/blah/src/graphics/spritefont.cpp
        dependencies/blah/src/graphics/subtexture.cpp
        dependencies/blah/src/graphics/texture.cpp

        dependencies/blah/src/input/input.cpp
        dependencies/blah/src/input/binding.cpp
        dependencies/blah/src/input/binding_registry.cpp

        dependencies/blah/src/containers/str.cpp

        dependencies/blah/src/images/aseprite.cpp
        dependencies/blah/src/images/font.cpp
        dependencies/blah/src/images/image.cpp
        dependencies/blah/src/images/packer.cpp

        dependencies/blah/src/math/calc.cpp
        dependencies/blah/src/math/circle.cpp
        dependencies/blah/src/math/color.cpp
        dependencies/blah/src/math/line.cpp
        dependencies/blah/src/math/mat3x2.cpp
        dependencies/blah/src/math/mat4x4.cpp
        dependencies/blah/src/math/point.cpp
        dependencies/blah/src/math/quad.cpp
        dependencies/blah/src/math/rect.cpp
        dependencies/blah/src/math/rectI.cpp
        dependencies/blah/src/math/stopwatch.cpp
        dependencies/blah/src/math/vec2.cpp

        dependencies/blah/src/streams/bufferstream.cpp
        dependencies/blah/src/streams/filestream.cpp
        dependencies/blah/src/streams/memorystream.cpp
        dependencies/blah/src/streams/stream.cpp

        dependencies/blah/src/internal/graphics_backend_gl.cpp
        dependencies/blah/src/internal/graphics_backend_d3d11.cpp
        dependencies/blah/src/internal/graphics_backend_dummy.cpp
        dependencies/blah/src/internal/platform_backend_sdl2.cpp
        dependencies/blah/src/internal/platform_backend_win32.cpp
        src/gui/StaticSprite.cpp src/gui/StaticSprite.h)

target_link_libraries(chess2 PUBLIC ${LIBS} SDL2)