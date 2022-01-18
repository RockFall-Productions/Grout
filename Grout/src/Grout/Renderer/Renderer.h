#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace Grout {
	class Renderer {
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array);
		//static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform);

		inline static RendererAPI::API get_api() { return RendererAPI::get_api();  }
	private:
		struct SceneData {
			glm::mat4 view_projection_matrix;
		};

		static SceneData* scene_data_;
	};
}