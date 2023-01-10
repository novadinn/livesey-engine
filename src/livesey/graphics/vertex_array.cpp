#include "vertex_array.h"

namespace Livesey {
    
    void VertexArray::create() {
	glCreateVertexArrays(1, &id_);
    }
    
    void VertexArray::destroy() {
	glDeleteVertexArrays(1, &id_);
    }

    void VertexArray::addVertexBuffer(VertexBuffer vb) {
	const std::vector<VertexAttribute>& attribs = vb.getAttributeList();
	if(attribs.size() == 0) {
	    LOG_ERR("Empty attribute list passed for function addVertexBuffer");
	    return;
	}
	
	int i = 0;
	size_t total = 0;
	
	for(i = 0; i < attribs.size(); ++i) {
	    total += attribs[i].getSize() * attribs[i].getCount();
	}

	bind();
	vb.bind();
	
	size_t off = 0;
	for(i = 0; i < attribs.size(); ++i) {
	    glVertexAttribPointer(i, attribs[i].getCount(), GL_FLOAT,
				  attribs[i].isNormalized(),
				  total, (void*)(off*attribs[i].getSize()));
	    glEnableVertexAttribArray(i);
	    off += attribs[i].getCount();
	}

	vbs_.push_back(vb);
    }
    
    void VertexArray::setIndexBuffer(IndexBuffer ib) {
	bind();
	ib.bind();
		
	ib_ = ib;
    }

    void VertexArray::bind() {
	glBindVertexArray(id_);
    }
    
    void VertexArray::unbind() {
	glBindVertexArray(0);
    }
}
