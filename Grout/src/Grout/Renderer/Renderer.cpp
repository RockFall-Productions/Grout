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
		

		uint32_t diffuseNr = 1;
		uint32_t specularNr = 1;
		for (uint32_t i = 0; i < obj->mesh->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = obj->mesh->textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_integer(("u_material." + name + number).c_str(), i, false);
			glBindTexture(GL_TEXTURE_2D, obj->mesh->textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		RenderCommand::DrawIndexed(obj->mesh_component.vertex_array);
	}
}