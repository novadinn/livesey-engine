#include "vertex_buffer.h"

namespace Livesey {

    void VertexBuffer::create(void* verts, uint size, std::vector<VertexAttribute> attr) {
	attr_lst_ = attr;
	glCreateBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, id_);
	glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
    }
    
    void VertexBuffer::destroy() {
	glDeleteBuffers(1, &id_);
    }
    
    void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id_);
    }
    
    void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
