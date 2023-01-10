#include "input.h"

#include "engine.h"

namespace Livesey {

    bool Input::isKeyPressed(int key) {
	GLFWwindow* wnd = Engine::getInstance()->getWindow()->getNativeWindow();
	int ls = glfwGetKey(wnd, key);
	return ls == GLFW_PRESS;
    }
    
    bool Input::isKeyReleased(int key) {
	GLFWwindow* wnd = Engine::getInstance()->getWindow()->getNativeWindow();
	int ls = glfwGetKey(wnd, key);
	return ls == GLFW_RELEASE;
    }
    
    bool Input::isMouseButtonPressed(int b) {
	GLFWwindow* wnd = Engine::getInstance()->getWindow()->getNativeWindow();
	int ls = glfwGetMouseButton(wnd, b);
	return ls == GLFW_PRESS;
    }

    bool Input::isMouseButtonReleased(int b) {
	GLFWwindow* wnd = Engine::getInstance()->getWindow()->getNativeWindow();
	int ls = glfwGetMouseButton(wnd, b);
	return ls == GLFW_RELEASE;
    }
    
    glm::dvec2 Input::getMousePosition() {
	GLFWwindow* wnd = Engine::getInstance()->getWindow()->getNativeWindow();
	double x, y;
	glfwGetCursorPos(wnd, &x, &y);

	return glm::dvec2(x, y);
    }
    
    double Input::getMouseX() {
	return getMousePosition().x;
    }
    
    double Input::getMouseY() {
	return getMousePosition().y;
    }
}
