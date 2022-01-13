#pragma once

#include "Grout/Renderer/Buffer.h"

namespace Grout {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) const = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) const = 0;

		static VertexArray* Create();
	};
}
 