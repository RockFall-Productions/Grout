#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"
#include "Grout/Scene/Object.h"

namespace Grout {
	class Renderer {
	public:
		inline static RendererAPI::API get_api() { return RendererAPI::get_api();  }
		
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(Camera& camera);
		
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));
		
		static void RenderObject(const Ref<Object>& obj, const Ref<Shader>& shader);
		static void RenderMeshObject(const Ref<Object>& obj, const Ref<Shader>& shader);
		
		static void EndScene();

	private:
		struct SceneData {
			glm::mat4 view_projection_matrix;
		};

		static Scope<SceneData> scene_data_;
	};
}