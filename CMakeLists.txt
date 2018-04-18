cmake_minimum_required(VERSION 3.11)

project( colorCube )

find_package(OpenGL REQUIRED)

set( SOURCES  
  src/Camera.h
  src/main.cpp
  src/Shader.h
)
add_executable( colorCube ${SOURCES} )

set(CMAKE_PREFIX_PATH "exten/glew-2.1.0")
set(CMAKE_LIBRARY_PATH "exten/glew-2.1.0/lib/Release/x64")
find_package(GLEW REQUIRED)
set(CMAKE_PREFIX_PATH "exten/opencv-3.4.1/build")
set(CMAKE_LIBRARY_PATH "exten/opencv-3.4.1/build/x64/vc14/lib")
find_package(OpenCV REQUIRED)

add_subdirectory(exten/glfw-3.2.1)
include_directories(
  exten/glm-0.9.8.5/glm/
  exten/glfw-3.2.1/include/
  exten/glew-2.1.0/include/
  exten/opencv-3.4.1/build/include/
)

target_link_libraries( colorCube
  glfw
  ${OPENGL_LIBRARIES}
  ${OpenCV_LIBS}
  ${GLEW_LIBRARIES}
  )