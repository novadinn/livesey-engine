#include "engine.h"

#include "graphics/shader.h"
#include "graphics/vertex_buffer.h"
#include "graphics/index_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/textures.h"
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

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
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
    
	Livesey::Shader shader;
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

	Livesey::VertexArray va;
	Livesey::VertexBuffer vb;
	Livesey::IndexBuffer ib;

	va.create();
	va.bind();

	std::vector<Livesey::VertexAttribute> attribs = {
	    Livesey::VertexAttribute(Livesey::AttributeType::VEC3, GL_FALSE),
	    Livesey::VertexAttribute(Livesey::AttributeType::VEC3, GL_FALSE),	
	    Livesey::VertexAttribute(Livesey::AttributeType::VEC2, GL_FALSE)
	};
	vb.create(vertices, sizeof(vertices), attribs);
	ib.create(indices, sizeof(indices));
    
	va.addVertexBuffer(vb);
	va.setIndexBuffer(ib);

	Livesey::Texture2D tex;
	tex.createFromFile("img/container.jpg");
    
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
	    case Livesey::EventType::I_KEY: {
		receivers_[i]->onKeyEvent(static_cast<Livesey::KeyEvent&>(e));
	    } break;
	    case Livesey::EventType::I_CHAR: {
		receivers_[i]->onCharEvent(static_cast<Livesey::CharEvent&>(e));
	    } break;
	    case Livesey::EventType::I_CURSOR_POS: {
		receivers_[i]->onCursorPosEvent(static_cast<Livesey::CursorPosEvent&>(e));
	    } break;
	    case Livesey::EventType::I_CURSOR_ENTER: {
		receivers_[i]->onCursorEnterEvent(static_cast<Livesey::CursorEnterEvent&>(e));
	    } break;
	    case Livesey::EventType::I_MOUSE_BUTTON: {
		receivers_[i]->onMouseButtonEvent(static_cast<Livesey::MouseButtonEvent&>(e));
	    } break;
	    case Livesey::EventType::I_SCROLL: {
		receivers_[i]->onScrollEvent(static_cast<Livesey::ScrollEvent&>(e));
	    } break;		
	    case Livesey::EventType::W_CLOSE: {
		receivers_[i]->onCloseEvent(static_cast<Livesey::CloseEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_SIZE: {
		receivers_[i]->onSizeEvent(static_cast<Livesey::SizeEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_FRAMEBUFFER_SIZE: {
		receivers_[i]->onFramebufferSizeEvent(static_cast<Livesey::FramebufferSizeEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_CONTENT_SCALE: {
		receivers_[i]->onContentScaleEvent(static_cast<Livesey::ContentScaleEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_POS: {
		receivers_[i]->onPosEvent(static_cast<Livesey::PosEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_ICONIFY: {
		receivers_[i]->onIconifyEvent(static_cast<Livesey::IconifyEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_MAXIMIZE: {
		receivers_[i]->onMaximizeEvent(static_cast<Livesey::MaximizeEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_FOCUS: {
		receivers_[i]->onFocusEvent(static_cast<Livesey::FocusEvent&>(e)); 
	    } break;
	    case Livesey::EventType::W_REFRESH: {
		receivers_[i]->onRefreshEvent(static_cast<Livesey::RefreshEvent&>(e));
	    } break;
	    }
	}
    }
}
