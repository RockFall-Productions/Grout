#pragma once

#include "Grout/Renderer/Buffer.h"

namespace Grout {
	//////////////////////////////////////////////////////////////////////
	//////////////////////////// VERTEX BUFFER ///////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t id_;
	};
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	//////////////////////////// INDEX BUFFER ////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t get_count() const { return count_; };
	private:
		uint32_t id_;
		uint32_t count_;
	};
	//////////////////////////////////////////////////////////////////////
}
