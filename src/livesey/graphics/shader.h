#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

namespace Livesey {
    
    struct Shader {

	void createFromSource(const char* vsrc, const char* fsrc);
	void destroy();

	void bind();
	void unbind();

	void setFloat1(const char* s, float v);
	void setFloat2(const char* s, const glm::vec2& v);
	void setFloat3(const char* s, const glm::vec3& v);
	void setFloat4(const char* s, const glm::vec4& v);

	void setInt1(const char* s, int v);
	void setInt2(const char* s, const glm::ivec2& v);
	void setInt3(const char* s, const glm::ivec3& v);
	void setInt4(const char* s, const glm::ivec4& v);

	void setUInt1(const char* s, uint v);
	void setUInt2(const char* s, const glm::uvec2& v);
	void setUInt3(const char* s, const glm::uvec3& v);
	void setUInt4(const char* s, const glm::uvec4& v);

	/* TODO: 
	   glUniform1fv
	   glUniform2fv
	   glUniform3fv
	   glUniform4fv

	   glUniform1iv
	   glUniform2iv
	   glUniform3iv
	   glUniform4iv

	   glUniform1uiv
	   glUniform2uiv
	   glUniform3uiv
	   glUniform4uiv
	*/
	
	void setMatrix2(const char* s, const glm::mat2& m);
	void setMatrix3(const char* s, const glm::mat3& m);
	void setMatrix4(const char* s, const glm::mat4& m);

	void setMatrix2x3(const char* s, const glm::mat2x3& m);
	void setMatrix3x2(const char* s, const glm::mat3x2& m);
	void setMatrix2x4(const char* s, const glm::mat2x4& m);
	void setMatrix4x2(const char* s, const glm::mat4x2& m);
	void setMatrix3x4(const char* s, const glm::mat3x4& m);
	void setMatrix4x3(const char* s, const glm::mat4x3& m);
	    
	inline uint getId() const { return id_; }
    
    private:
	uint id_;
    };
}

#endif // SHADER_H
