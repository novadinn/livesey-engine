#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "../platform.h"
#include "vertex_attribute.h"

#include <vector>

namespace Livesey {
    
    struct VertexBuffer {
	void create(void* verts, uint size, std::vector<VertexAttribute> attr);
	void destroy();
	
	void bind();
	void unbind();
	
	inline const std::vector<VertexAttribute>& getAttributeList() { return attr_lst_; }
	inline uint getId() const { return id_; }
	
    private:
	std::vector<VertexAttribute> attr_lst_;
	uint id_;
    };
}

#endif // VERTEX_BUFFER_H
