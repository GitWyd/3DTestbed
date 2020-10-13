cmake_minimum_required(VERSION 3.17)

# set project name and version
project(3DTestbed VERSION 1.0)
configure_file(cmake/3DTestbed.h.in TutorialConfig.h)


# set c++ standard
set(CMAKE_CXX_STANDARD 14)

set($3DTestbed_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set($3DTestbed_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

include_directories(${3DTestbed_INCLUDE_DIR})

# add executable
add_executable(3DTestbed
        src/Application.cpp
        include/3DTestbed.h
        include/VertexBuffer.h
        src/VertexBuffer.cpp
        include/IndexBuffer.h
        src/IndexBuffer.cpp
        include/Renderer.h
        src/Renderer.cpp
        src/VertexArray.cpp
        include/VertexArray.h
        src/VertexBufferLayout.cpp
        include/VertexBufferLayout.h
        src/Shader.cpp
        include/Shader.h
        include/Texture.h
        src/Texture.cpp
        include/vendor/stb_image/stb_image.h
        include/vendor/stb_image/stb_image.cpp
        include/vendor/ImGUI/imconfig.h
        include/vendor/ImGUI/imgui.cpp
        include/vendor/ImGUI/imgui.h
        include/vendor/ImGUI/imgui_demo.cpp
        include/vendor/ImGUI/imgui_draw.cpp
        include/vendor/ImGUI/imgui_impl_glfw.cpp
        include/vendor/ImGUI/imgui_impl_glfw.h
        include/vendor/ImGUI/imgui_impl_opengl3.cpp
        include/vendor/ImGUI/imgui_impl_opengl3.h
        include/vendor/ImGUI/imgui_internal.h
        include/vendor/ImGUI/imgui_widgets.cpp
        include/vendor/ImGUI/imstb_rectpack.h
        include/vendor/ImGUI/imstb_textedit.h
        include/vendor/ImGUI/imstb_truetype.h
        include/tests/TestClearcolor.h
        src/tests/TestClearColor.cpp
        src/tests/Test.cpp
        include/tests/Test.h
        src/tests/TestTexture2D.cpp
        include/tests/TestTexture2D.h
        src/tests/Test3DScene.cpp
        include/tests/Test3DScene.h
        include/tests/geometries/geometry.h
        src/tests/geometries/geometry.cpp
        include/tests/geometries/sphere.h
        src/tests/geometries/sphere.cpp
        include/tests/geometries/cylinder.h
        src/tests/geometries/cylinder.cpp
        include/tests/geometries/triangle.h
        src/tests/geometries/triangle.cpp
        )



set(3DTestbed_HEADER_FILES ${3DTestbed_INCLUDE_DIR}/3DTestbed.h)
set(3DTestbed_SOURCE_FILES ${3DTestbed_SOURCE_DIR}/main.cpp)

# add library

# find and include OpenGL for graphics support
set(3DTestbed_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include)
set(3DTestbed_LIBRARIES "")
set(OpenGL_GL_PREFERENCE LEGACY)
if (UNIX)
    find_package(OpenGL REQUIRED)
    if (OpenGL_FOUND)
        message(STATUS "OPENGL FOUND")
        target_include_directories(3DTestbed PRIVATE ${OpenGL_INCLUDE_DIRS})
        target_link_libraries(3DTestbed PRIVATE ${OpenGL_LIBRARIES} GL)
        set(3DTestbed_INCLUDE_DIRS ${3DTestbed_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})
        set(3DTestbed_LIBRARIES ${3DTestbed_LIBRARIES} ${OpenGL_LIBRARIES})
    endif()
else()
    find_package(OPENGL REQUIRED) # find and include OpenGL
    if (OPENGL_FOUND)
        message(STATUS "OPENGL FOUND")
        target_include_directories(3DTestbed PRIVATE ${OPENGL_INCLUDE_DIRS})
        target_link_libraries(3DTestbed PRIVATE ${OPENGL_LIBRARIES})
        set(3DTestbed_INCLUDE_DIRS ${3DTestbed_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})
        set(3DTestbed_LIBRARIES ${3DTestbed_LIBRARIES} ${OpenGL_LIBRARIES})
    endif()
endif()

# find and include glfw for graphics support
find_package(glfw3 CONFIG REQUIRED)
if (glfw3_FOUND)
    message(STATUS "GLFW FOUND")
    target_include_directories(3DTestbed PRIVATE ${glfw3_INCLUDE_DIRS})
    target_link_libraries(3DTestbed PRIVATE ${glfw3_LIBRARIES} glfw)
    set(3DTestbed_INCLUDE_DIRS ${3DTestbed_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})
    set(3DTestbed_LIBRARIES ${3DTestbed_LIBRARIES} ${glfw3_LIBRARIES})
endif()

# find and include GLEW for graphics support
find_package(GLEW REQUIRED) # GLEW
if (GLEW_FOUND)
    message(STATUS "GLEW FOUND")
    target_include_directories(3DTestbed PRIVATE ${GLEW_INCLUDE_DIRS})
    target_link_libraries(3DTestbed PRIVATE ${GLEW_LIBRARIES})
    set(3DTestbed_INCLUDE_DIRS ${3DTestbed_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
    set(3DTestbed_LIBRARIES ${3DTestbed_LIBRARIES} ${GLEW_LIBRARIES})
endif()

# find and include glm for graphics support
find_package(glm CONFIG REQUIRED) # glm
if (glm_FOUND)
    message(STATUS "GLM FOUND")
    target_include_directories(3DTestbed PRIVATE ${glm_INCLUDE_DIRS})
    target_link_libraries(3DTestbed PRIVATE ${glm_LIBRARIES} glm)
    set(3DTestbed_INCLUDE_DIRS ${3DTestbed_INCLUDE_DIRS} ${glm_INCLUDE_DIRS})
    set(3DTestbed_LIBRARIES ${3DTestbed_LIBRARIES} ${glm_LIBRARIES})
endif()

# include directories for build target
target_include_directories(3DTestbed PUBLIC "${PROJECT_BINARY_DIR}")
