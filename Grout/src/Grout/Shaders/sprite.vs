#version 330 core

// location defines attribute's position on VAO position
// Position (vec2 - position, vec2 - texture coordinates)
layout (location = 0) in vec4 vertex;

// and the texture coordinates
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	// Assigns the texture coordinates from Vertex Data to "texCoords" in fragement shader
   texCoords = vertex.zw;

	// Transformations on coordinates: local -> model -> projection(clip)
	// Z is set to 0.0f due to 2D nature of the game
	// W is set to 1.0 and will not change due to using ortographic projection
   gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}

