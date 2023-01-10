#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "../platform.h"

namespace Livesey {

    struct IndexBuffer {
	void create(uint* inds, uint size);
	void destroy();
	
	void bind();
	void unbind();

	inline uint getIndicesCount() const { return c_; }
	
	inline uint getId() const { return id_; }
    private:
	uint id_;
	uint c_;
    };
}

#endif // INDEX_BUFFER_H
