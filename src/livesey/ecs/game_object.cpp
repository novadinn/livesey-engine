#include "game_object.h"

#include "scene.h"
#include "ecs.h"
#include "../log.h"

namespace Livesey {

    GameObject::GameObject(Scene* scene) : scene_(scene) {}

    template<class T, typename... Args>
    T* GameObject::addComponent(Args&&... args) {
	if(hasComponent<T>()) {
	    LOG_ERR("Object already has component");
	    return nullptr;
	}

	T* c = new T(std::forward<Args>(args)...);
	scene_->registry_[this].insert({getComponentID<T>(), c});
	
	return c;
    }

    template<class T>
    T* GameObject::getComponent() {
	view v = scene_->registry_[this];
	uint id = getComponentID<T>();

	for(view::iterator it = v.begin(); it != v.end(); ++it) {
	    if(it->first == id)
		return it->second;
	}

	return nullptr;
    }
    
    template<class T>
    bool GameObject::hasComponent() {
	view v = scene_->registry_[this];
	uint id = getComponentID<T>();

	for(view::iterator it = v.begin(); it != v.end(); ++it) {
	    if(it->first == id)
		return true;
	}

	return false;
    }
    
    template<class T>
    void GameObject::removeComponent() {
	view v = scene_->registry_[this];
	uint id = getComponentID<T>();

	for(view::iterator it = v.begin(); it != v.end(); ++it) {
	    if(it->first == id) {
		delete it->second;
		v.erase(it);
		break;
	    }
	}
    }
}
