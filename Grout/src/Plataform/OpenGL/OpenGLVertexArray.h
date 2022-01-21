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
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) override;

		// Getters
		virtual const std::vector<Ref<VertexBuffer>>& get_vertex_buffers() const override { return vertex_buffers_; };
		virtual const Ref<IndexBuffer>& get_index_buffer() const override { return index_buffer_; };
	private:
		uint32_t id_;

		std::vector<Ref<VertexBuffer>> vertex_buffers_;
		Ref<IndexBuffer> index_buffer_;
	};
}
