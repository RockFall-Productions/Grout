#include "grtpch.h"
#include "EBO.h"

namespace Grout {
	EBO::EBO(GLuint* indices, GLsizeiptr size) {
		// Gera 1 objeto de EBO
		glGenBuffers(1, &ID);
		// Bind para a utilização do EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		// Inserção dos indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void EBO::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void EBO::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void EBO::Delete() {
		glDeleteBuffers(1, &ID);
	}
}