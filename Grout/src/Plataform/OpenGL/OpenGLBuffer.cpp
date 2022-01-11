#include "grtpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Grout {
	//////////////////////////////////////////////////////////////////////
	//////////////////////////// VERTEX BUFFER ///////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : id_(0)
	{
		// Creates one VBO object
		glGenBuffers(1, &id_);
		// Binds it for it's use
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		// Inserts vertices data into VBO
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &id_);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id_);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////
	//////////////////////////// INDEX BUFFER ////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) 
		: id_(0), count_(count)
	{
		// Gera 1 objeto de EBO
		glGenBuffers(1, &id_);
		// Bind para a utilização do EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		// Inserção dos indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &id_);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	/////////////////////////////////////////////////////////////////////////
}