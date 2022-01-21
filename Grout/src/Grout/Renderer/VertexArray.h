#pragma once

#include "Grout/Renderer/Buffer.h"

namespace Grout {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& get_vertex_buffers() const = 0;
		virtual const Ref<IndexBuffer>& get_index_buffer() const = 0;

		static VertexArray* Create();
	};
}
 