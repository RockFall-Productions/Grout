#pragma once

#include "RendererAPI.h"

namespace Grout {
	class RenderCommand {
	public:
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			renderer_api_->SetViewport(x, y, width, height);
		}

		// Changes the color in which the screen is cleared with
		inline static void SetClearColor(const glm::vec4& color) {
			renderer_api_->SetClearColor(color);
		}

		// Clear the screen with the setted color
		inline static void Clear() {
			renderer_api_->Clear();
		}

		// Draws everything in the given vertex_array into the screen
		inline static void DrawIndexed(const Ref<VertexArray>& vertex_array) {
			renderer_api_->DrawIndexed(vertex_array);
		}

	private:
		static RendererAPI* renderer_api_;

	};
}