#ifndef TEXTURE_H
#define TEXTURE_H

#include "../platform.h"

namespace Livesey {

    struct Texture2D {
	void createFromFile(const char* p);
	void destroy();

	void bind();
	void unbind();
	
	inline uint getWidth() const { return w_; }
	inline uint getHeight() const { return h_; }

	inline uint getId() const { return id_; }
    private:
	uint w_, h_;
	uint id_;
    };
}

#endif
