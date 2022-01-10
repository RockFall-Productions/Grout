#include "grtpch.h"
#include "VAO.h"

namespace Grout {
	VAO::VAO() {
		glGenVertexArrays(1, &ID);
	}

	void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		VBO.Bind();

		// Specify the location and data format of the array of generic 
		// vertex attributes to use when rendering. 
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

		// Enables the use of currently bound vertex array object
		glEnableVertexAttribArray(layout);

		VBO.Unbind();
	}

	void VAO::Bind() {
		glBindVertexArray(this->ID);
	}

	void VAO::Unbind() {
		glBindVertexArray(0);
	}

	void VAO::Delete() {
		glDeleteVertexArrays(1, &ID);
	}
}