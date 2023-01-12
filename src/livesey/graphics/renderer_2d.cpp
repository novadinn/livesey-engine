#include "renderer_2d.h"

#include "vertex_attribute.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

namespace Livesey {

    static const char* qshadervsrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";
    static const char* qshaderfsrc = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform vec4 inColor;

void main()
{
	FragColor = texture(texture1, TexCoord) * inColor;
}
)";

    static Shader qshader;
    static VertexArray va;
    static VertexBuffer vb;
    static IndexBuffer ib;
    static glm::vec4 cl_col;
    
    void Renderer2D::onInit() {
	qshader.createFromSource(qshadervsrc, qshaderfsrc);

	float vertices[] = {
	    0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
	    0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
	    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
	};
	uint indices[] = {
	    0, 1, 3,
	    1, 2, 3
	};

	va.create();
	va.bind();

	std::vector<VertexAttribute> attribs = {
	    VertexAttribute(AttributeType::VEC3, GL_FALSE),
	    VertexAttribute(AttributeType::VEC2, GL_FALSE)
	};
	vb.create(vertices, sizeof(vertices), attribs);
	ib.create(indices, sizeof(indices));
    
	va.addVertexBuffer(vb);
	va.setIndexBuffer(ib);
    }
    
    void Renderer2D::onDestroy() {
	qshader.destroy();
	ib.destroy();
	vb.destroy();
	va.destroy();
    }

    void Renderer2D::begin(const glm::mat4& view, const glm::mat4& proj) {
	qshader.bind();
	qshader.setMatrix4("view", view);
	qshader.setMatrix4("projection", proj);
	va.bind();
    }
    
    void Renderer2D::drawSprite(const glm::mat4& model, SpriteRenderer* r) {
	qshader.setMatrix4("model", model);
	qshader.setVec4("inColor", r->color);
	r->texture.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void Renderer2D::end() {
	qshader.unbind();
	va.unbind();
    }

    void Renderer2D::clear() {
	glClearColor(cl_col.x, cl_col.y, cl_col.z, cl_col.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void Renderer2D::setClearColor(const glm::vec4& c) {
	cl_col = c;
    }
}
