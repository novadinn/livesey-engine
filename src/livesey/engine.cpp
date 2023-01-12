#include "engine.h"

#include "graphics/shader.h"
#include "graphics/vertex_buffer.h"
#include "graphics/index_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/textures.h"
#include "graphics/orthographic_camera.h"
#include "graphics/renderer_2d.h"
#include "ecs/game_object.h"
#include "ecs/scene.h"
#include "ecs/components.h"
#include "log.h"
#include "imgui_receiver.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Livesey {
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
    
	Renderer2D::onInit();
	Renderer2D::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	Texture2D tex;
	tex.createFromFile("img/container.jpg");	
	
	Scene* sc = new Scene();
	GameObject* obj = sc->createGameObject("Box");
	SpriteRenderer* r = obj->addComponent<SpriteRenderer>();
	r->texture = tex;
	r->color = glm::vec4(0.8f, 0.5f, 0.1f, 1.0f);
	Transform* t = obj->addComponent<Transform>();
	t->position += glm::vec2(0.5f, 0.0f);

	GameObject* obj2 = sc->createGameObject("Second");
	SpriteRenderer* r2 = obj2->addComponent<SpriteRenderer>();
	r2->texture = tex;
	r2->color = glm::vec4(0.2f, 0.5f, 0.7f, 1.0f);
	Transform* t2 = obj2->addComponent<Transform>();
	t2->position -= glm::vec2(0.5f, 0.0f);

	OrthographicCamera camera(800, 600);
	
	while (!glfwWindowShouldClose(wnd)) {
	    Renderer2D::clear();
	    
	    for(int i = 0; i < receivers_.size(); ++i) {
		receivers_[i]->onUpdate();
	    }

	    imgr_->begin();

	    static bool show_demo_window = true;
	    if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	    Renderer2D::begin(camera.getViewMatrix(), camera.getProjectionMatrix());
	    Renderer2D::drawSprite(t->getModelMatrix(), r);
	    Renderer2D::drawSprite(t2->getModelMatrix(), r2);
	    Renderer2D::end();

	    for(int i = 0; i < receivers_.size(); ++i) {
		receivers_[i]->onDraw();
	    }

	    imgr_->end();
	    
	    wnd_->onUpdate();
	}

	Renderer2D::onDestroy();

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
