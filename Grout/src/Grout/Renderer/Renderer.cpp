#include "grtpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Grout {
	// HACK: Ideally we should have a tiny database for Renderer data
	Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		scene_data_->view_projection_matrix = camera.get_viewprojection_matrix();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array)
	{
		shader->Bind();
		shader->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, false);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}
}