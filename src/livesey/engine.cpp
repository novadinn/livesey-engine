#include "engine.h"

#include "graphics/shader.h"
#include "graphics/vertex_buffer.h"
#include "graphics/index_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/textures.h"
#include "graphics/orthographic_camera.h"
#include "log.h"
#include "imgui_receiver.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Livesey {

    static const char* texvsrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";
    static const char* texfsrc = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
}
)";

    Engine* Engine::inst_ = nullptr;
    
    Engine::Engine() {
	if(inst_ != 0)
	    LOG_ERR_FATAL("Engine instance already exists");
	
	inst_ = this;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	wnd_ = new Window("Livesey",
			  std::bind(&Engine::dispatchEvent, this, std::placeholders::_1),
			  800, 600);

	imgr_ = new ImGuiReceiver();
	addEventReceiver(imgr_);
    }

    void Engine::run() {
	GLFWwindow* wnd = wnd_->getNativeWindow();
	
	for(int i = 0; i < receivers_.size(); ++i) {
	    receivers_[i]->onCreate();
	}
    
	Shader shader;
	shader.createFromSource(texvsrc, texfsrc); 

	float vertices[] = {
	    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};
	uint indices[] = {
	    0, 1, 3,
	    1, 2, 3
	};

	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	va.create();
	va.bind();

	std::vector<VertexAttribute> attribs = {
	    VertexAttribute(AttributeType::VEC3, GL_FALSE),
	    VertexAttribute(AttributeType::VEC3, GL_FALSE),	
	    VertexAttribute(AttributeType::VEC2, GL_FALSE)
	};
	vb.create(vertices, sizeof(vertices), attribs);
	ib.create(indices, sizeof(indices));
    
	va.addVertexBuffer(vb);
	va.setIndexBuffer(ib);

	Texture2D tex;
	tex.createFromFile("img/container.jpg");

	OrthographicCamera camera(800, 600);
	
	while (!glfwWindowShouldClose(wnd)) {
	    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    
	    for(int i = 0; i < receivers_.size(); ++i) {
		receivers_[i]->onUpdate();
	    }

	    imgr_->begin();

	    static bool show_demo_window = true;
	    if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	    tex.bind();

	    shader.bind();
	    shader.setMatrix4("model", glm::mat4(1.0f));
	    shader.setMatrix4("view", camera.getViewMatrix());
	    shader.setMatrix4("projection", camera.getProjectionMatrix());
	    va.bind();
	    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	    for(int i = 0; i < receivers_.size(); ++i) {
		receivers_[i]->onDraw();
	    }

	    imgr_->end();
	    
	    wnd_->onUpdate();
	}

	for(int i = 0; i < receivers_.size(); ++i) {
	    receivers_[i]->onDestroy();
	    delete receivers_[i];
	}
    }

    void Engine::addEventReceiver(EventReceiver* receiver) {
	receivers_.push_back(receiver);
    }
    
    void Engine::dispatchEvent(Event& e) {
	for(int i = 0; i < receivers_.size(); ++i) {
	    switch(e.getType()) {
	    case EventType::I_KEY: {
		receivers_[i]->onKeyEvent(static_cast<KeyEvent&>(e));
	    } break;
	    case EventType::I_CHAR: {
		receivers_[i]->onCharEvent(static_cast<CharEvent&>(e));
	    } break;
	    case EventType::I_CURSOR_POS: {
		receivers_[i]->onCursorPosEvent(static_cast<CursorPosEvent&>(e));
	    } break;
	    case EventType::I_CURSOR_ENTER: {
		receivers_[i]->onCursorEnterEvent(static_cast<CursorEnterEvent&>(e));
	    } break;
	    case EventType::I_MOUSE_BUTTON: {
		receivers_[i]->onMouseButtonEvent(static_cast<MouseButtonEvent&>(e));
	    } break;
	    case EventType::I_SCROLL: {
		receivers_[i]->onScrollEvent(static_cast<ScrollEvent&>(e));
	    } break;		
	    case EventType::W_CLOSE: {
		receivers_[i]->onCloseEvent(static_cast<CloseEvent&>(e)); 
	    } break;
	    case EventType::W_SIZE: {
		receivers_[i]->onSizeEvent(static_cast<SizeEvent&>(e)); 
	    } break;
	    case EventType::W_FRAMEBUFFER_SIZE: {
		receivers_[i]->onFramebufferSizeEvent(static_cast<FramebufferSizeEvent&>(e)); 
	    } break;
	    case EventType::W_CONTENT_SCALE: {
		receivers_[i]->onContentScaleEvent(static_cast<ContentScaleEvent&>(e)); 
	    } break;
	    case EventType::W_POS: {
		receivers_[i]->onPosEvent(static_cast<PosEvent&>(e)); 
	    } break;
	    case EventType::W_ICONIFY: {
		receivers_[i]->onIconifyEvent(static_cast<IconifyEvent&>(e)); 
	    } break;
	    case EventType::W_MAXIMIZE: {
		receivers_[i]->onMaximizeEvent(static_cast<MaximizeEvent&>(e)); 
	    } break;
	    case EventType::W_FOCUS: {
		receivers_[i]->onFocusEvent(static_cast<FocusEvent&>(e)); 
	    } break;
	    case EventType::W_REFRESH: {
		receivers_[i]->onRefreshEvent(static_cast<RefreshEvent&>(e));
	    } break;
	    }
	}
    }
}
