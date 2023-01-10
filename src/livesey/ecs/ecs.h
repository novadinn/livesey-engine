#ifndef ECS_H
#define ECS_H

namespace Livesey {
    
    uint comp_c = 0;
    template<class T>
	uint getComponentID() {
	static uint id = comp_c++;
	return id;
    }

    typedef std::unordered_map<uint, Component*> view;
    typedef std::unordered_map<GameObject*, view> registry;
}

#endif
