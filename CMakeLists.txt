cmake_minimum_required(VERSION 3.17)

project(livesey)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include_directories("include" "include/imgui")

add_executable(${PROJECT_NAME} "src/glad.c" "src/main.cpp" "include/imgui/imgui.cpp" "include/imgui/imgui_demo.cpp" "include/imgui/imgui_draw.cpp" "include/imgui/imgui_tables.cpp" "include/imgui/imgui_widgets.cpp" "include/imgui/imgui.cpp" "include/imgui/backends/imgui_impl_glfw.cpp" "include/imgui/backends/imgui_impl_opengl3.cpp")

target_link_libraries(${PROJECT_NAME} GL dl glfw)


