#version 330 core

// location defines attribute's position on VAO
// Position (vec2 - position, vec2 - texture coordinates)
layout (location = 0) in vec4 vertex;

// texture and color of particle
out vec2 texCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;

void main()
{
	float scale = 10.0f;
	texCoords = vertex.zw;
	ParticleColor = color;
    gl_Position = projection * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}

