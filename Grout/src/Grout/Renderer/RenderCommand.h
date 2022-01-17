#pragma once

#include "RendererAPI.h"

namespace Grout {
	class RenderCommand {
	public:
		// Changes the color in which the screen is cleared with
		inline static void SetClearColor(const glm::vec4& color) {
			renderer_api_->SetClearColor(color);
		}

		// Clear the screen with the setted color
		inline static void Clear() {
			renderer_api_->Clear();
		}

		// Draws everything in the given vertex_array into the screen
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) {
			renderer_api_->DrawIndexed(vertex_array);
		}

	private:
		static RendererAPI* renderer_api_;

	};
}