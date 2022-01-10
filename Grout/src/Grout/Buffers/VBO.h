#pragma once

#include "Grout/Core.h"
#include <glad/glad.h>

// Holds the VBO ID and performs all need actions
namespace Grout {
	class VBO {
	public:
		// Reference ID of the VBO
		GLuint ID;

		// Creates one VBO object and stores 
		// it's ID into class variable.
		// 
		// Receive the vertices array and the size in bytes.
		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};
}