#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Livesey {

    void Shader::createFromSource(const char* vsrc, const char* fsrc) {
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *src = (const GLchar *)vsrc;
	glShaderSource(vs, 1, &src, 0);

	glCompileShader(vs);

	GLint compp = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compp);
	if(compp == GL_FALSE) {
	    GLint ml = 0;
	    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &ml);

	    std::vector<GLchar> log(ml);
	    glGetShaderInfoLog(vs, ml, &ml, &log[0]);

	    glDeleteShader(vs);

	    LOG_ERR("Failed to load Vertex Shader. \n%s\n", &log[0]);

	    return;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	src = (const GLchar *)fsrc;
	glShaderSource(fs, 1, &src, 0);

	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &compp);
	if (compp == GL_FALSE) {
	    GLint ml = 0;
	    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &ml);

	    std::vector<GLchar> log(ml);
	    glGetShaderInfoLog(fs, ml, &ml, &log[0]);
	
	    glDeleteShader(fs);
	    glDeleteShader(vs);

	    LOG_ERR("Failed to load Fragment Shader. \n%s\n", &log[0]);
	
	    return;
	}

	id_ = glCreateProgram();

	glAttachShader(id_, vs);
	glAttachShader(id_, fs);

	glLinkProgram(id_);

	GLint linkp = 0;
	glGetProgramiv(id_, GL_LINK_STATUS, (int *)&linkp);
	if (linkp == GL_FALSE) {
	    GLint ml = 0;
	    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &ml);
	    
	    std::vector<GLchar> log(ml);
	    glGetProgramInfoLog(id_, ml, &ml, &log[0]);

	    glDeleteProgram(id_);
	    glDeleteShader(vs);
	    glDeleteShader(fs);

	    LOG_ERR("Failed to create Program. \n%s\n", &log[0]);
	
	    return;
	}
	
	glDetachShader(id_, vs);
	glDetachShader(id_, fs);

	return;
    }

    void Shader::destroy() {
	glDeleteProgram(id_);
    }
    
    void Shader::bind() {
	glUseProgram(id_);
    }

    void Shader::unbind() {
	glUseProgram(0);
    }

    void Shader::setFloat1(const char* s, float v) {
	glUniform1f(glGetUniformLocation(id_, s), v);
    }
    
    void Shader::setFloat2(const char* s, const glm::vec2& v) {
	glUniform2f(glGetUniformLocation(id_, s), v.x, v.y);
    }
    
    void Shader::setFloat3(const char* s, const glm::vec3& v) {
	glUniform3f(glGetUniformLocation(id_, s), v.x, v.y, v.z);
    }
    
    void Shader::setFloat4(const char* s, const glm::vec4& v) {
	glUniform4f(glGetUniformLocation(id_, s), v.x, v.y, v.z, v.w);
    }
        
    void Shader::setInt1(const char* s, int v) {
	glUniform1i(glGetUniformLocation(id_, s), v);
    }
    
    void Shader::setInt2(const char* s, const glm::ivec2& v) {
	glUniform2i(glGetUniformLocation(id_, s), v.x, v.y);
    }
    
    void Shader::setInt3(const char* s, const glm::ivec3& v) {
	glUniform3i(glGetUniformLocation(id_, s), v.x, v.y, v.z);
    }
    
    void Shader::setInt4(const char* s, const glm::ivec4& v) {
	glUniform4i(glGetUniformLocation(id_, s), v.x, v.y, v.z, v.w);
    }
    
    void Shader::setUInt1(const char* s, uint v) {
	glUniform1ui(glGetUniformLocation(id_, s), v);
    }
    
    void Shader::setUInt2(const char* s, const glm::uvec2& v) {
	glUniform2ui(glGetUniformLocation(id_, s), v.x, v.y);
    }
    
    void Shader::setUInt3(const char* s, const glm::uvec3& v) {
	glUniform3ui(glGetUniformLocation(id_, s), v.x, v.y, v.z);
    }
    
    void Shader::setUInt4(const char* s, const glm::uvec4& v) {
	glUniform4ui(glGetUniformLocation(id_, s), v.x, v.y, v.z, v.w);
    }    
        
    void Shader::setMatrix2(const char* s, const glm::mat2& m) {
	glUniformMatrix2fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix3(const char* s, const glm::mat3& m) {
	glUniformMatrix3fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix4(const char* s, const glm::mat4& m) {
	glUniformMatrix4fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }    
    
    void Shader::setMatrix2x3(const char* s, const glm::mat2x3& m) {
	glUniformMatrix2x3fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix3x2(const char* s, const glm::mat3x2& m) {
	glUniformMatrix3x2fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix2x4(const char* s, const glm::mat2x4& m) {
	glUniformMatrix2x4fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix4x2(const char* s, const glm::mat4x2& m) {
	glUniformMatrix4x2fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix3x4(const char* s, const glm::mat3x4& m) {
	glUniformMatrix3x4fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
    
    void Shader::setMatrix4x3(const char* s, const glm::mat4x3& m) {
	glUniformMatrix4x3fv(glGetUniformLocation(id_, s), 1, GL_FALSE, glm::value_ptr(m));
    }
}
