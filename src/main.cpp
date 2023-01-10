#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "livesey/window.cpp"
#include "livesey/imgui_receiver.cpp"
#include "livesey/engine.cpp"
#include "livesey/input.cpp"
#include "livesey/graphics/vertex_array.cpp"
#include "livesey/graphics/vertex_buffer.cpp"
#include "livesey/graphics/index_buffer.cpp"
#include "livesey/graphics/shader.cpp"
#include "livesey/graphics/textures.cpp"
#include "livesey/graphics/vertex_attribute.h"
#include "livesey/graphics/orthographic_camera.cpp"

int main(int argc, char** argv) {	
    Livesey::Engine* engine = new Livesey::Engine();
    engine->run();

    delete engine;
    return 0;
}
