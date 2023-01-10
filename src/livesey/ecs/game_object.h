#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

namespace Livesey {

    struct Scene;
    
    struct GameObject {
	GameObject(Scene* scene);
	
	template<class T, typename... Args>
	T* addComponent(Args&&... args);
	template<class T>
	T* getComponent();
	template<class T>
	bool hasComponent();
	template<class T>
	void removeComponent();

    private:
	Scene* scene_;
    };
}

#endif // GAME_OBJECT_H
