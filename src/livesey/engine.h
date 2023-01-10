#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "event_receiver.h"

#include <vector>

namespace Livesey {

    struct Engine {
	Engine();

	void run();
	void addEventReceiver(EventReceiver* receiver);
	void dispatchEvent(Event& e);

	inline static Engine* getInstance() { return inst_; }
	inline Window* getWindow() const { return wnd_; }
	
    private:
	Window* wnd_;
	static Engine* inst_;
	
	std::vector<EventReceiver*> receivers_;
	ImGuiReceiver* imgr_;
    };
}

#endif // ENGINE_H
