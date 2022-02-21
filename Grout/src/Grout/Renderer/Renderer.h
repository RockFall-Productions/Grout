#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"
#include "Grout/Scene/Object.h"

namespace Grout {
	class Renderer {
	public:
		struct LightData {
			glm::vec3 light_pos = {40.0f, 90.0f, 40.0f };
			glm::vec3 light_dir = {-1.0f / 3.0f, -1.0f / 3.0f, -1.0f / 3.0f };

			glm::vec3 ambient_light_colour = { 0.06f, 0.14f, 0.59f };
			float ambient_light_strength = 0.36f;

			glm::vec3 light_diffuse = { 1.0f, 1.0f, 1.0f };
			glm::vec3 light_specular = { 1.0f, 1.0f, 1.0f };

			int texture_id = 0;
			int texture_offset = 0;
		};

		inline static RendererAPI::API get_api() { return RendererAPI::get_api();  }
		
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(Camera& camera);
		
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));
		
		static void RenderObject(const Ref<Object>& obj, const Ref<Shader>& shader);
		static void RenderMeshObject(const Ref<Object>& obj, const Ref<Shader>& shader, LightData light_data);
		static void RenderModelObject(const Ref<Object>& obj, const Ref<Shader>& shader, Renderer::LightData light_data);
		static void RenderSkybox(const Ref<Object>& obj, const Ref<Camera>& camera, const Ref<Shader>& shader);

		static void EndScene();

	private:
		struct SceneData {
			glm::mat4 view_projection_matrix;
		};


		static Scope<SceneData> scene_data_;
	};
}