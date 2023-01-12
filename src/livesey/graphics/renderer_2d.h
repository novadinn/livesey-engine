#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "../ecs/components.h"
#include "../ecs/game_object.h"

#include <glm/glm.hpp>

namespace Livesey {

    struct Renderer2D {

	static void onInit();
	static void onDestroy();

	static void begin(const glm::mat4& view, const glm::mat4& proj);
	// TODO: later on, each component should store a reference to its gameobject
	static void drawSprite(const glm::mat4& model, SpriteRenderer* r);
	static void end();

	static void clear();
	static void setClearColor(const glm::vec4& c);
    };
}

#endif // RENDERER_2D_H
