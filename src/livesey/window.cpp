#include "window.h"

#include "log.h"

namespace Livesey {
    
    Window::Window(std::string title, wincall cb, uint w, uint h) {
	data_.w = w;
	data_.h = h;
	data_.cb = cb;
	
	wnd_ = glfwCreateWindow(data_.w, data_.h, title.c_str(), 0, 0);
	if(wnd_ == 0) {
	    LOG_ERR_FATAL("Failed to create GLFW window");
	    glfwTerminate();
	}
	
	glfwMakeContextCurrent(wnd_);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    LOG_ERR_FATAL("Failed to initialize GLAD");
	}

	glfwSetWindowUserPointer(wnd_, &data_);
	
	glfwSetKeyCallback(wnd_, [](GLFWwindow* wnd, int k, int sc, int acts, int mods) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    KeyEvent e(k, sc, acts, mods);
	    data.cb(e);
	});
	glfwSetCharCallback(wnd_, [](GLFWwindow* wnd, unsigned int cp) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    CharEvent e(cp);
	    data.cb(e);
	});
	glfwSetCursorPosCallback(wnd_, [](GLFWwindow* wnd, double x, double y) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    CursorPosEvent e(x, y);
	    data.cb(e);
	});
	glfwSetCursorEnterCallback(wnd_, [](GLFWwindow* wnd, int ent) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    CursorEnterEvent e(ent);
	    data.cb(e);
	});
	glfwSetMouseButtonCallback(wnd_, [](GLFWwindow* wnd, int b, int acts, int mods) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    MouseButtonEvent e(b, acts, mods);
	    data.cb(e);
	});
	glfwSetScrollCallback(wnd_, [](GLFWwindow* wnd, double x, double y) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    ScrollEvent e(x, y);
	    data.cb(e);
	});
	
	glfwSetWindowCloseCallback(wnd_, [](GLFWwindow* wnd) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    CloseEvent e;
	    data.cb(e);
	});
	glfwSetWindowSizeCallback(wnd_, [](GLFWwindow* wnd, int w, int h) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    SizeEvent e(w, h);
	    data.w = w;
	    data.h = h;
	    data.cb(e);
	});
	glfwSetFramebufferSizeCallback(wnd_, [](GLFWwindow* wnd, int w, int h) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    FramebufferSizeEvent e(w, h);
	    data.cb(e);
	});
	glfwSetWindowContentScaleCallback(wnd_, [](GLFWwindow* wnd, float x, float y) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    ContentScaleEvent e(x, y);
	    data.cb(e);
	});
	glfwSetWindowPosCallback(wnd_, [](GLFWwindow* wnd, int x, int y) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    PosEvent e(x, y);
	    data.cb(e);
	});
	glfwSetWindowIconifyCallback(wnd_, [](GLFWwindow* wnd, int ic) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    IconifyEvent e(ic);
	    data.cb(e);
	});
	glfwSetWindowMaximizeCallback(wnd_, [](GLFWwindow* wnd, int m) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    MaximizeEvent e(m);
	    data.cb(e);
	});
	glfwSetWindowFocusCallback(wnd_, [](GLFWwindow* wnd, int f) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    FocusEvent e(f);
	    data.cb(e);
	});
	glfwSetWindowRefreshCallback(wnd_, [](GLFWwindow* wnd) {
	    WindowData data = *(WindowData*)glfwGetWindowUserPointer(wnd);
	    RefreshEvent e;
	    data.cb(e);
	});
    }

    Window::~Window() {
	glfwDestroyWindow(wnd_);
	glfwTerminate();
    }

    void Window::onUpdate() {
	glfwSwapBuffers(wnd_);
        glfwPollEvents();
    }
}
