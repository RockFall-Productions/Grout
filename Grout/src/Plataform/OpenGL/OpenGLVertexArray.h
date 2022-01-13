#pragma once

#include "Grout/Renderer/VertexArray.h"

namespace Grout {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray() {}
		virtual ~OpenGLVertexArray() {}

		// Herdado por meio de VertexArray
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) const override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) const override;
	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
		std::shared_ptr<IndexBuffer> index_buffers_;
	};
}
