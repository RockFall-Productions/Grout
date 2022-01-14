#pragma once

#include "Grout/Renderer/RendererAPI.h"

namespace Grout {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		// Herdado por meio de RendererAPI
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) override;
	};
}

