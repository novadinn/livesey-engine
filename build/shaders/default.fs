#version 330 core
			
in vec3 v_Position;
in vec2 v_TexCoords;

uniform sampler2D sprite;

out vec4 color;

void main() {
    color = texture(sprite, v_TexCoords); // vec4(v_Position * 0.5 + 0.5, 1.0);
}
