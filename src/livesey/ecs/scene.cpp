#include "scene.h"

#include "game_object.h"

namespace Livesey {
    
    GameObject* Scene::createGameObject(const char* s) {
	GameObject* obj = new GameObject(this);
	registry_.insert({obj, view()});

	return obj;
    }
    
    void Scene::destroyGameObject(GameObject* obj) {
	for(registry::iterator it = registry_.begin(); it != registry_.end(); ++it) {
	    if(it->first == obj) {
		view v = it->second;
		
		for(view::iterator c = v.begin(); c != v.end(); ++c) {
		    Component* comp = c->second;
		    delete comp;
		}
		
		delete obj;
		registry_.erase(it);
		break;
	    }
	}
    }
}
