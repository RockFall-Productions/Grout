#include <Grout.h>
#include <Grout/Core/EntryPoint.h>

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"




class TestLayer : public Grout::Layer {
public:
	TestLayer() : Layer("Testing"), camera_(glm::vec3(0.0f, 0.0f, 10.0f), 32.0f, 18.0f) {
		// world space positions of our cubes
		glm::vec3 cubePositions[] = {
			glm::vec3(1.0f,   1.0f, 0.0f),
			glm::vec3(-1.0f, -1.0f,  0.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (int i = 0; i < 10; i++)
		{
			cubes_.push_back(Grout::Object("Cube", cubePositions[i]));
		}

		Grout::Ref<Grout::VertexBuffer> vertex_buffer;
		vertex_buffer.reset(Grout::VertexBuffer::Create(cubes_[0].cube_component.vertices, sizeof(cubes_[0].cube_component.vertices)));
		Grout::BufferLayout layout = {
			{Grout::ShaderDataType::Float3, "a_position"},
			{Grout::ShaderDataType::Float2, "a_texture" }
		};

		vertex_buffer->set_layout(layout);

		vertex_array_.reset(Grout::VertexArray::Create());

		vertex_array_->AddVertexBuffer(vertex_buffer);

		Grout::Ref<Grout::IndexBuffer> index_buffer;
		index_buffer.reset(Grout::IndexBuffer::Create(cubes_[0].cube_component.indices, sizeof(cubes_[0].cube_component.indices) / sizeof(uint32_t)));
		vertex_array_->SetIndexBuffer(index_buffer);
		
		shader_.reset(Grout::Shader::Create("assets/shaders/texture.glsl"));
		texture_ = Grout::Texture2D::Create("assets/images/textures/pocoyo.png");

		std::dynamic_pointer_cast<Grout::OpenGLShader>(shader_)->uniform_set_integer("u_image", 0, true);

		//texture_ = Grout::Texture2D::Create("assets/images/textures/grass.png");
	}

	void OnUpdate() override {

		// Clears the background color
		Grout::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		Grout::RenderCommand::Clear();

		/* Z ROTATION
		if (Grout::Input::is_key_pressed(GRT_KEY_Q)) 
			camera_.get_transform().add_rotation(glm::vec3(0.0f, 0.0f, 1.0f) * Grout::Time::delta_time_f());
		
		else if (Grout::Input::is_key_pressed(GRT_KEY_E))
			camera_.get_transform().add_rotation(glm::vec3(0.0f, 0.0f, -1.0f) * Grout::Time::delta_time_f());
		// Y ROTATION
		if (Grout::Input::is_key_pressed(GRT_KEY_R))
			camera_.get_transform().add_rotation(glm::vec3(0.0f, 1.0f, 0.0f) * Grout::Time::delta_time_f());

		else if (Grout::Input::is_key_pressed(GRT_KEY_T))
			camera_.get_transform().add_rotation(glm::vec3(0.0f, -1.0f, 0.0f) * Grout::Time::delta_time_f());
		// X ROTATION
		if (Grout::Input::is_key_pressed(GRT_KEY_Z))
			camera_.get_transform().add_rotation(glm::vec3(1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());

		else if (Grout::Input::is_key_pressed(GRT_KEY_X))
			camera_.get_transform().add_rotation(glm::vec3(-1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());
		*/

		if (Grout::Input::is_key_pressed(GRT_KEY_A))
			camera_.get_transform().add_position(glm::vec3(-1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());
		
		else if (Grout::Input::is_key_pressed(GRT_KEY_D))
			camera_.get_transform().add_position(glm::vec3(1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());
		
		if (Grout::Input::is_key_pressed(GRT_KEY_W))
			camera_.get_transform().add_position(glm::vec3(0.0f, 1.0f, 0.0f) * Grout::Time::delta_time_f());
		
		else if (Grout::Input::is_key_pressed(GRT_KEY_S))
			camera_.get_transform().add_position(glm::vec3(0.0f, -1.0f, 0.0f) * Grout::Time::delta_time_f());

		if (Grout::Input::is_key_pressed(GRT_KEY_F))
			camera_.get_transform().add_position(glm::vec3(0.0f, 0.0f, -1.0f) * Grout::Time::delta_time_f());

		else if (Grout::Input::is_key_pressed(GRT_KEY_G))
			camera_.get_transform().add_position(glm::vec3(0.0f, 0.0f, 1.0f) * Grout::Time::delta_time_f());

		// Rendering the Scene
		Grout::Renderer::BeginScene(camera_);

		//Grout::MaterialRef material = new Grout::Material(shader_);

		//std::dynamic_pointer_cast<Grout::OpenGLShader>(shader_)->uniform_set_vector4f("u_color", cubesColor);

		for (auto cube : cubes_)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cube.transform.get_position());
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			texture_->Bind(0);
			Grout::Renderer::Submit(shader_, vertex_array_, model);
		}
		Grout::Renderer::EndScene();

		// To-do: Threads
		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Test color", glm::value_ptr(cubesColor));

		ImGui::End();
	}

	void OnEvent(Grout::Event& event) override {
		Grout::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Grout::KeyPressedEvent>(GRT_BIND_EVENT_FN(TestLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Grout::KeyPressedEvent event) {

		return false;
	}

private:
	// Buffer
	Grout::Ref<Grout::Shader> shader_;
	Grout::Ref<Grout::Texture2D> texture_;
	Grout::Ref<Grout::VertexArray> vertex_array_;
	glm::vec4 cubesColor = glm::vec4(0.0f);

	Grout::Ref<Grout::VertexArray> square_VA_;
	Grout::Ref<Grout::VertexArray> cube_VA_;

	std::vector<Grout::Object> cubes_;

	Grout::Camera camera_;
};

class Sandbox : public Grout::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {

	}
};

Grout::Application* Grout::CreateApplication() {
	return new Sandbox();
}