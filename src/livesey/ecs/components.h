#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../graphics/textures.h"
#include "../graphics/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Livesey {

    struct Component {
	virtual ~Component() = default;
    };

    struct Transform : public Component {	
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 size = glm::vec2(1.0f);
	float rotation = 0.0f;

	glm::mat4 getModelMatrix() const {
	    glm::mat4 model = glm::mat4(1.0f);
	    model = glm::translate(model, glm::vec3(position, 0.0f));
	    model = glm::translate(model, glm::vec3(0.5f * size.x,
						    0.5f * size.y, 0.0f));
	    model = glm::rotate(model, glm::radians(rotation),
				glm::vec3(0.0f, 0.0f, 1.0f));
	    model = glm::translate(model, glm::vec3(-0.5f * size.x,
						    -0.5f * size.y, 0.0f));
	    model = glm::scale(model, glm::vec3(size, 1.0f));

	    return model;
	}
    };

    struct Tag : public Component {
	char* tag;
    };

    struct SpriteRenderer : public Component  {
	Texture2D texture;
	glm::vec4 color = glm::vec4(1.0f);
    };
}

#endif // COMPONENTS_H
