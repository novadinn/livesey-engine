#include "textures.h"

namespace Livesey {

    void Texture2D::createFromFile(const char* p) {
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, nc;
	unsigned char *data = stbi_load(p, &w, &h, &nc, 0);
	
	if (data) {
	    w_ = (uint)w;
	    h_ = (uint)h;

	    GLenum int_fmt;
	    GLenum data_fmt;
	    if(nc == 4) {
		int_fmt = GL_RGBA8;
		data_fmt = GL_RGBA;
	    } else if(nc == 3) {
		int_fmt = GL_RGB8;
		data_fmt = GL_RGB;
	    }
	    
	    glTexImage2D(GL_TEXTURE_2D, 0, int_fmt, w_, h_, 0, data_fmt, GL_UNSIGNED_BYTE, data);
	} else {
	    LOG_ERR("Failed to load texture at path %s\n", p);
	}
	
	stbi_image_free(data);
    }
    
    void Texture2D::destroy() {
	glDeleteTextures(1, &id_);
    }

    void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, id_);
    }
    
    void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
    }
}
