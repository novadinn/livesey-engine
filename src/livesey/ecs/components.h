#ifndef COMPONENTS_H
#define COMPONENTS_H

namespace Livesey {

    struct Component {
	virtual ~Component() = default;
    };

    struct Transform : public Component {
	glm::vec2 position;
	glm::vec2 size;
	float rotation;
    };
}

#endif // COMPONENTS_H
