#include "grtpch.h"
#include "VBO.h"

namespace Grout {
	VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
		// Creates one VBO object
		glGenBuffers(1, &ID);
		// Binds it for it's use
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		// Inserts vertices data into VBO
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void VBO::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Delete() {
		glDeleteBuffers(1, &ID);
	}
}