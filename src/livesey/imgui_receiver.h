#ifndef IMGUI_RECEIVER_H
#define IMGUI_RECEIVER_H

#include "event_receiver.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace Livesey {
    
    struct ImGuiReceiver : public EventReceiver{
	
	virtual void onCreate() override;
	virtual void onDestroy() override;

	void begin();
	void end();

	void setClearColor(ImVec4 c) { cl_col_ = c; }
	
    private:
	ImVec4 cl_col_;
    };
}
    
#endif // IMGUI_RECEIVER_H
