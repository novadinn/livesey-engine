#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_Position;
out vec2 v_TexCoords;

void main() {
    v_Position = a_Position;
    v_TexCoords = a_TexCoords;
    gl_Position = projection * view * model * vec4(a_Position, 1.0);	
}
