#version 330 core

// Texture coordinates from Vertex Shader
in vec2 texCoords;
out vec4 color;

// Texture slot where the Shader is stored -> Usually 0
uniform sampler2D image;
// With this we can change the color of sprites through code
uniform vec4 spriteColor;

void main()
{
   color = vec4(spriteColor) * texture(image, texCoords);
}

