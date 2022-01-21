#include "grtpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

#include "Plataform/OpenGL/OpenGLShader.h"

namespace Grout {
	// HACK: Ideally we should have a tiny database for Renderer data
	Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(Camera& camera)
	{
		scene_data_->view_projection_matrix = camera.get_viewprojection_matrix();
	}
	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, false);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}
}