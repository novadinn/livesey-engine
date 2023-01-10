#ifndef INPUT_H
#define INPUT_H

#include <glm/glm.hpp>

namespace Livesey {

    struct Input {
	static bool isKeyPressed(int key);
	static bool isKeyReleased(int key);
	static bool isMouseButtonPressed(int b);
	static bool isMouseButtonReleased(int b);
	static glm::dvec2 getMousePosition();
	static double getMouseX();
	static double getMouseY();
    };
}

#endif // INPUT_H
