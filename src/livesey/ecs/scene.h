#ifndef SCENE_H
#define SCENE_H

#include "components.h"
#include "ecs.h"
#include "../platform.h"

#include <unordered_map>

namespace Livesey {

    struct GameObject;
    
    struct Scene {

	GameObject* createGameObject(const char* s);
	void destroyGameObject(GameObject* obj);
	
    private:
	registry registry_;

	friend struct GameObject;
    };
}
#endif // SCENE_H
