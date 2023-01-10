#include "index_buffer.h"

namespace Livesey {
    void IndexBuffer::create(uint* inds, uint size) {
	c_ = size / sizeof(uint);
	
	glCreateBuffers(1, &id_);

	glBindBuffer(GL_ARRAY_BUFFER, id_);
	glBufferData(GL_ARRAY_BUFFER, size, inds, GL_STATIC_DRAW);
    }
    
    void IndexBuffer::destroy() {
	glDeleteBuffers(1, &id_);
    }
	
    void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    }
    
    void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
