#include <Grout.h>

#include "imgui/imgui.h"

class TestLayer : public Grout::Layer {
public:
	TestLayer() : Layer("Testing"), camera_(glm::vec3(0.0f, 0.0f, 10.0f), 32.0f, 18.0f) {
		// Creation of Vertex Array
		vertex_array_.reset(Grout::VertexArray::Create());
		
		float vertices[4 * 7] = {
			// Position --- Color
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		};

		std::shared_ptr<Grout::VertexBuffer> vertex_buffer;
		// Creation of Vertex Buffer
		vertex_buffer.reset(Grout::VertexBuffer::Create(vertices, sizeof(vertices)));
		// Setting the Vertex Buffer Layout
		Grout::BufferLayout layout = {
			{ Grout::ShaderDataType::Float3, "a_position"},
			{ Grout::ShaderDataType::Float4, "a_color"}
		};
		vertex_buffer->set_layout(layout);
		// Adding this VertexBuffer to the VertexArray
		vertex_array_->AddVertexBuffer(vertex_buffer);

		// Setting up the Index Buffer and adding it to the VertexArray
		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<Grout::IndexBuffer> index_buffer;
		index_buffer.reset(Grout::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertex_array_->SetIndexBuffer(index_buffer);

		square_VA_.reset(Grout::VertexArray::Create());
		float vertices2[4 * 7] = {
			// Position --- Color
			-0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.3f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.2f, 0.3f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.2f, 1.0f, 1.0f
		};
		std::shared_ptr<Grout::VertexBuffer> squareVB;
		squareVB.reset(Grout::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVB->set_layout(layout);

		square_VA_->AddVertexBuffer(squareVB);

		uint32_t indices2[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Grout::IndexBuffer> squareIB;
		squareIB.reset(Grout::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		square_VA_->SetIndexBuffer(squareIB);

		float verticesCubes[6 * 6 * 7] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
						
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
			
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
						
		 0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
						   
		-0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
					
		-0.5f,  0.5f, -0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.4f, 0.2f, 1.0f
		};
		
		std::shared_ptr<Grout::VertexBuffer> cubeVB;
		cubeVB.reset(Grout::VertexBuffer::Create(verticesCubes, sizeof(verticesCubes)));

		cubeVB->set_layout(layout);

		cube_VA_.reset(Grout::VertexArray::Create());
		cube_VA_->AddVertexBuffer(cubeVB);

		uint32_t indicesCube[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
								  11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
								  21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
								  31, 32, 33, 34, 35 };
		//uint32_t indicesCube[] = { 2, 1, 0, 5, 4, 3, 8, 7, 6, 11, 10,
		//						  9, 14, 13, 12, 17, 16, 15, 20, 19, 18,
		//						  23, 22, 21, 26, 25, 24, 29, 28, 27, 32,
		//						  31, 30, 35, 34, 33 };
		//uint32_t indicesCube[] = { 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
		//20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

		std::shared_ptr<Grout::IndexBuffer> cubeIB;
		cubeIB.reset(Grout::IndexBuffer::Create(indicesCube, sizeof(indicesCube) / sizeof(uint32_t)));
		cube_VA_->SetIndexBuffer(cubeIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			uniform mat4 u_view_projection;

			out vec3 v_position;
			out vec4 v_color;

			void main() {
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_view_projection * vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_position;
			in vec4 v_color;

			void main() {
				color = v_color;
			}
		)";

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			uniform mat4 u_view_projection;
			uniform mat4 model;

			out vec3 v_position;
			out vec4 v_color;

			void main() {
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_view_projection * model * vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_position;
			in vec4 v_color;

			void main() {
				color = v_color;
			}
		)";

		shader_.reset(new Grout::Shader());
		shader_->CompileAndLink(vertexSrc.c_str(), fragmentSrc.c_str());

		shader2_.reset(new Grout::Shader());
		shader2_->CompileAndLink(vertexSrc2.c_str(), fragmentSrc2.c_str());
	}

	void OnUpdate() override {

		// Clears the background color
		Grout::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		Grout::RenderCommand::Clear();

		// Z ROTATION
		if (Grout::Input::is_key_pressed(GRT_KEY_Q)) 
			camera_.add_rotation(glm::vec3(0.0f, 0.0f, 0.1f));
		
		else if (Grout::Input::is_key_pressed(GRT_KEY_E))
			camera_.add_rotation(glm::vec3(0.0f, 0.0f, -0.1f));
		// Y ROTATION
		if (Grout::Input::is_key_pressed(GRT_KEY_R))
			camera_.add_rotation(glm::vec3(0.0f, 0.1f, 0.0f));

		else if (Grout::Input::is_key_pressed(GRT_KEY_T))
			camera_.add_rotation(glm::vec3(0.0f, -0.1f, 0.0f));
		// X ROTATION
		if (Grout::Input::is_key_pressed(GRT_KEY_Z))
			camera_.add_rotation(glm::vec3(0.1f, 0.0f, 0.0f));

		else if (Grout::Input::is_key_pressed(GRT_KEY_X))
			camera_.add_rotation(glm::vec3(-0.1f, 0.0f, 0.0f));

		if (Grout::Input::is_key_pressed(GRT_KEY_Q))
			camera_.add_rotation(glm::vec3(0.0f, 0.0f, 0.1f));

		else if (Grout::Input::is_key_pressed(GRT_KEY_E))
			camera_.add_rotation(glm::vec3(0.0f, 0.0f, -0.1f));
		
		if (Grout::Input::is_key_pressed(GRT_KEY_A))
			camera_.add_position(glm::vec3(-0.05f, 0.0f, 0.0f));
		
		else if (Grout::Input::is_key_pressed(GRT_KEY_D))
			camera_.add_position(glm::vec3(0.05f, 0.0f, 0.0f));
		
		if (Grout::Input::is_key_pressed(GRT_KEY_W))
			camera_.add_position(glm::vec3(0.0f, 0.05f, 0.0f));
		
		else if (Grout::Input::is_key_pressed(GRT_KEY_S))
			camera_.add_position(glm::vec3(0.0f, -0.05f, 0.0f));

		if (Grout::Input::is_key_pressed(GRT_KEY_F))
			camera_.add_position(glm::vec3(0.0f, 0.0f, -0.5f));

		else if (Grout::Input::is_key_pressed(GRT_KEY_G))
			camera_.add_position(glm::vec3(0.0f, 0.0f, 0.5f));
		

		//camera_.set_rotation(glm::vec3(0.0f, 0.0f, 45.0f));
		//camera_.set_position(glm::vec3(0.5f, 0.5f, 0.0f));

		// Rendering the Scene
		Grout::Renderer::BeginScene(camera_);
		//Grout::Renderer::Submit(shader_, square_VA_);

		// world space positions of our cubes
		glm::vec3 cubePositions[] = {
			glm::vec3( 1.0f,   1.0f, 0.0f),
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
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader2_->uniform_set_matrix4("model", model);

			Grout::Renderer::Submit(shader2_, cube_VA_);
		}
		Grout::Renderer::EndScene();

		// To-do: Threads
		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override {
		
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
	std::shared_ptr<Grout::Shader> shader_;
	std::shared_ptr<Grout::Shader> shader2_;
	std::shared_ptr<Grout::VertexArray> vertex_array_;

	std::shared_ptr<Grout::VertexArray> square_VA_;
	std::shared_ptr<Grout::VertexArray> cube_VA_;

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