#pragma once

#include "Grout/Renderer/VertexArray.h"
#include <glad/glad.h>

namespace Grout {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		// Bindings
		virtual void Bind() const override;
		virtual void Unbind() const override;

		// Add a vertex or index buffer to the vertex array
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;

		// Getters
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const override { return vertex_buffers_; };
		virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const override { return index_buffer_; };
	private:
		uint32_t id_;

		std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
		std::shared_ptr<IndexBuffer> index_buffer_;
	};
}
