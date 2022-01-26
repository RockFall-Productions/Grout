#include "BoidWorldLayer.h"

using namespace Grout;

BoidWorldLayer::BoidWorldLayer() : Layer("BoidWorldLayer")
{
	auto& window = Application::get_instance().get_window();
	CreateCamera(window.get_width(), window.get_height());

}

void BoidWorldLayer::OnAttach()
{
	// All setup stuff here
	world_map_ = World();
	world_map_.Start();

	float vertices[6 * 6 * 7] = {
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

	uint32_t indices[36] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
								  11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
								  21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
								  31, 32, 33, 34, 35 };

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

	

	Grout::Ref<Grout::VertexBuffer> vertex_buffer;
	vertex_buffer.reset(Grout::VertexBuffer::Create(vertices, sizeof(vertices)));
	Grout::BufferLayout layout = {
		{Grout::ShaderDataType::Float3, "a_position"},
		{Grout::ShaderDataType::Float4, "a_color" }
	};

	vertex_buffer->set_layout(layout);

	vertex_array_.reset(Grout::VertexArray::Create());

	vertex_array_->AddVertexBuffer(vertex_buffer);

	Grout::Ref<Grout::IndexBuffer> index_buffer;
	index_buffer.reset(Grout::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	vertex_array_->SetIndexBuffer(index_buffer);

	shader_.reset(Grout::Shader::Create("assets/shaders/mesh.glsl"));

	for (int i = 0; i < 10; i++)
	{
		cubes_.push_back(CreateRef<Grout::Object>("Cube", cubePositions[i]));
		cubes_[i]->mesh_component.vertex_array = vertex_array_;
	}
}

void BoidWorldLayer::OnDetach()
{
}

void BoidWorldLayer::OnUpdate()
{
	// Update
	CameraMovement();

	// Render
	// Clears the background color
	Grout::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	Grout::RenderCommand::Clear();

	Renderer::BeginScene(*camera_);

	world_map_.OnRender();

	for (auto cube : cubes_)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::translate(model, cube->transform.get_position());
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		// 
		//glm::mat4 transform = cube->transform.get_transform();

		//Grout::Renderer::Submit(shader_, cube->mesh_component.vertex_array, model);
		//Grout::Renderer::Submit(shader_, cube->mesh_component.vertex_array, cube->transform.get_transform());
		
		Grout::Renderer::RenderObject(cube, shader_);
	}

	Renderer::EndScene();
}

void BoidWorldLayer::OnImGuiRender()
{
}

void BoidWorldLayer::OnEvent(Grout::Event& event)
{
}

void BoidWorldLayer::CreateCamera(uint32_t width, uint32_t height)
{
	camera_ = CreateScope<Camera>(glm::vec3(0.0f, 1.0f, 0.0f), width, height);
}

void BoidWorldLayer::CameraMovement()
{
	// Z ROTATION
	if (Grout::Input::is_key_pressed(GRT_KEY_Q))
		camera_->get_transform().add_rotation(glm::vec3(0.0f, 0.0f, 1.0f) * Grout::Time::delta_time_f());

	else if (Grout::Input::is_key_pressed(GRT_KEY_E))
		camera_->get_transform().add_rotation(glm::vec3(0.0f, 0.0f, -1.0f) * Grout::Time::delta_time_f());
	// Y ROTATION
	if (Grout::Input::is_key_pressed(GRT_KEY_R))
		camera_->get_transform().add_rotation(glm::vec3(0.0f, 1.0f, 0.0f) * Grout::Time::delta_time_f());

	else if (Grout::Input::is_key_pressed(GRT_KEY_T))
		camera_->get_transform().add_rotation(glm::vec3(0.0f, -1.0f, 0.0f) * Grout::Time::delta_time_f());
	// X ROTATION
	if (Grout::Input::is_key_pressed(GRT_KEY_Z))
		camera_->get_transform().add_rotation(glm::vec3(1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());

	else if (Grout::Input::is_key_pressed(GRT_KEY_X))
		camera_->get_transform().add_rotation(glm::vec3(-1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());


	if (Grout::Input::is_key_pressed(GRT_KEY_A))
		camera_->get_transform().add_position(glm::vec3(-1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());

	else if (Grout::Input::is_key_pressed(GRT_KEY_D))
		camera_->get_transform().add_position(glm::vec3(1.0f, 0.0f, 0.0f) * Grout::Time::delta_time_f());

	if (Grout::Input::is_key_pressed(GRT_KEY_W))
		camera_->get_transform().add_position(glm::vec3(0.0f, 1.0f, 0.0f) * Grout::Time::delta_time_f());

	else if (Grout::Input::is_key_pressed(GRT_KEY_S))
		camera_->get_transform().add_position(glm::vec3(0.0f, -1.0f, 0.0f) * Grout::Time::delta_time_f());

	if (Grout::Input::is_key_pressed(GRT_KEY_F))
		camera_->get_transform().add_position(glm::vec3(0.0f, 0.0f, -1.0f) * Grout::Time::delta_time_f());

	else if (Grout::Input::is_key_pressed(GRT_KEY_G))
		camera_->get_transform().add_position(glm::vec3(0.0f, 0.0f, 1.0f) * Grout::Time::delta_time_f());
}
