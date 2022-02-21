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

		glm::mat4 transform = obj->transform.get_transform_matrix();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, false);

		obj->mesh_component.vertex_array->Bind();
		RenderCommand::DrawIndexed(obj->mesh_component.vertex_array);
	}
	
	void Renderer::RenderMeshObject(const Ref<Object>& obj, const Ref<Shader>& shader, LightData light_data)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, false);

		glm::mat4 transform = obj->transform.get_transform_matrix();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_light_pos", light_data.light_pos, false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_light_dir", glm::normalize(light_data.light_dir), false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_bool("u_block_light", false, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_ambient_color", light_data.ambient_light_colour, false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_float("u_ambient_strenght", light_data.ambient_light_strength, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_camera_pos", Grout::Camera::get_main()->get_transform().get_position(), false);

		//std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_ambient", light_data.ambient_light_colour, false);
		//std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_float("u_t_ambient_strength", light_data.ambient_light_strength, false);

		//std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_light_diffuse", light_data.light_diffuse, false);
		//std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_light_specular", light_data.light_specular, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_view_pos", Camera::get_main()->get_transform().get_position(), false);

		RenderCommand::SetFlatShaderProvokingVertex(GRT_FIRST_VERTEX_CONVENTION);
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

	void Renderer::RenderModelObject(const Ref<Object>& obj, const Ref<Shader>& shader, Renderer::LightData light_data)
	{

		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_view_projection", scene_data_->view_projection_matrix, false);

		glm::mat4 transform = obj->transform.get_transform_matrix();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_matrix4("u_transform", transform, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_light_pos", light_data.light_pos, false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_light_dir", glm::normalize(light_data.light_dir), false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_bool("u_block_light", false, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_ambient", light_data.ambient_light_colour, false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_float("u_t_ambient_strength", light_data.ambient_light_strength, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_light_diffuse", light_data.light_diffuse, false);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_t_light_specular", light_data.light_specular, false);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_vector3f("u_view_pos", Camera::get_main()->get_transform().get_position(), false);
		
		// TODO: change?

		obj->model_3D->Render(shader);

		/*
		// Setting up Caustic effect
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		glEnable(GL_BLEND);

		GLfloat sPlane[4] = { 0.05, 0.03, 0.0, 0.0 };
		GLfloat tPlane[4] = { 0.0, 0.03, 0.05, 0.0 };

		float causticScale = 1;

		sPlane[0] = 0.05 * causticScale;
		sPlane[1] = 0.03 * causticScale;

		tPlane[1] = 0.03 * causticScale;
		tPlane[2] = 0.05 * causticScale;

		glColor3f(1.0, 1.0, 1.0);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_2D);

		for (int i = 0; i < obj->model_3D->get_meshes().size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, light_data.texture_id);

			std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_bool("u_block_light", true, true);
			std::dynamic_pointer_cast<OpenGLShader>(shader)->uniform_set_integer("texture_diffuse1", i, true);

			glBindVertexArray(obj->model_3D->get_meshes()[i].VAO);
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(obj->model_3D->get_meshes()[i].indices.size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			
			glActiveTexture(GL_TEXTURE0);
		}

		glActiveTexture(GL_TEXTURE0);

		// Returning to normal
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);*/
	}
}