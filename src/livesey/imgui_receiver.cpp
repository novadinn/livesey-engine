#include "imgui_receiver.h"

#include "engine.h"

namespace Livesey {
    
    void ImGuiReceiver::onCreate() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
	ImGui::StyleColorsLight();

	GLFWwindow* window = Engine::getInstance()->getWindow()->getNativeWindow();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	cl_col_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    }

    void ImGuiReceiver::onDestroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    }

    void ImGuiReceiver::begin() {
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    
    void ImGuiReceiver::end() {
	ImGuiIO& io = ImGui::GetIO();
	Engine* e = Engine::getInstance();
	io.DisplaySize = ImVec2((float)e->getWindow()->getWidth(),
				(float)e->getWindow()->getHeight());
	ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
