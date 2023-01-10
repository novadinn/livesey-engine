#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "../platform.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

#include <vector>

namespace Livesey {

    struct VertexArray {

	void create();
	void destroy();

	void addVertexBuffer(VertexBuffer vb);
	void setIndexBuffer(IndexBuffer ib);

	void bind();
	void unbind();

	inline uint getId() const { return id_; }
    private:
	uint id_;
	
	std::vector<VertexBuffer> vbs_;
	IndexBuffer ib_;
    };
}

#endif
