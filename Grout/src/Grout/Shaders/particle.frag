#version 330 core

// Texture coordinates from Vertex Shader
in vec2 texCoords;
in vec4 ParticleColor;
out vec4 color;

// Texture slot where the Shader is stored -> Usually 0
uniform sampler2D sprite;

void main()
{
	// Color based on sprite and defined color
   color = (texture(sprite, texCoords) * ParticleColor);
}

