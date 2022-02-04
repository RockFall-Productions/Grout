#pragma once

#include "RendererAPI.h"

namespace Grout {
	class RenderCommand {
	public:
		inline static void Init() {
			renderer_api_->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			renderer_api_->SetViewport(x, y, width, height);
		}

		inline static void SetDepthFunc(GRTenum type) {
			renderer_api_->SetDepthFunc(type);
		}

		inline static void SetFlatShaderProvokingVertex(GRTenum type) {
			renderer_api_->SetFlatShaderProvokingVertex(type);
		}
		
		inline static void SetAntialias(GRTenum type) {
			renderer_api_->SetFlatShaderProvokingVertex(type);
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

		// Draws everything in the given vertex_array into the screen
		inline static void CreateCubeMap(uint32_t* cubemap_texture, std::string* faces_cubemap) {
			renderer_api_->CreateCubeMap(cubemap_texture, faces_cubemap);
		}



	private:
		static Scope<RendererAPI> renderer_api_;

	};
}