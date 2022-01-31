#include "grtpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

#include "Plataform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Grout {
	// HACK: Ideally we should have a tiny database for Renderer data
	Scope<Renderer::SceneData> Renderer::scene_data_ = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

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

	void Renderer::RenderObject(const Ref<Object>& obj, const Ref<Shader>& shader)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, false);

		glm::mat4 transform = obj->transform.get_transform();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, false);

		obj->mesh_component.vertex_array->Bind();
		RenderCommand::DrawIndexed(obj->mesh_component.vertex_array);
	}
	
	void Renderer::RenderMeshObject(const Ref<Object>& obj, const Ref<Shader>& shader)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, false);

		glm::mat4 transform = obj->transform.get_transform();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, false);

		obj->mesh_component.vertex_array->Bind();

		// TODO: change?

		RenderCommand::DrawIndexed(obj->mesh_component.vertex_array);
	}

	void Renderer::RenderSkybox(const Ref<Object>& obj, const Ref<Camera>& camera, const Ref<Shader>& shader)
	{
		RenderCommand::SetDepthFunc(GRT_LEQUAL);

		shader->Bind();
		// Changing matrix so only rotation does apply
		glm::quat orientation = camera->get_transform().get_orientation();
		glm::mat4 view = glm::toMat4(orientation);
		view = glm::inverse(view);
		glm::mat4 view_projection_matrix = camera->get_projection_matrix() * view;

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", view_projection_matrix, false);

		obj->skybox_component->vertex_array->Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, obj->skybox_component->cubemap_texture);
		RenderCommand::DrawIndexed(obj->skybox_component->vertex_array);

		RenderCommand::SetDepthFunc(GRT_LESS);
	}

	void Renderer::RenderModelObject(const Ref<Object>& obj, const Ref<Shader>& shader)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, true);

		glm::mat4 transform = obj->transform.get_transform();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, true);

		//obj->mesh_component.vertex_array->Bind();

		// TODO: change?

		obj->model_3D->Render(shader);
	}
}