#ifndef WINDOW_H
#define WINDOW_H

#include "platform.h"
#include "events.h"

#include <string>
#include <functional>

namespace Livesey {

    typedef std::function<void(Event&)> wincall;

    struct Window {
	Window(std::string title, wincall cb, uint w, uint h);
	~Window();

	void onUpdate();
	
	inline GLFWwindow* getNativeWindow() const { return wnd_; }
	inline uint getWidth() const { return data_.w; }
	inline uint getHeight() const { return data_.h; }
	
    private:
	struct WindowData {
	    uint w;
	    uint h;
	    wincall cb;
	};

	GLFWwindow* wnd_;
	WindowData data_;
	std::string title_;
    };
}
    
#endif // WINDOW_H
