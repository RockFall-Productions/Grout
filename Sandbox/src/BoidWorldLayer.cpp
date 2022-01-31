#include "BoidWorldLayer.h"
#include <glm/glm/gtc/type_ptr.hpp>

using namespace Grout;

BoidWorldLayer::BoidWorldLayer() : Layer("BoidWorldLayer")
{
	auto& window = Application::get_instance().get_window();
	CreateCamera(window.get_width(), window.get_height());

	flock = Flock();
}

void BoidWorldLayer::OnAttach()
{
	// All setup stuff here
	world_map_ = World();
	world_map_.Start();

	// Boid setup
	boid_object_ = Grout::CreateRef<Grout::Object>("Boid", glm::vec3(0.0f, 0.0f, 0.0f));
	boid_object_->model_3D = Grout::CreateRef<Grout::Model>("assets/objects/fish/fish_idle.obj");
	boid_shader_.reset(Grout::Shader::Create("assets/shaders/model.glsl"));
	boid_object_->transform.set_scale(glm::vec3(0.3f));

	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
	flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));
}

void BoidWorldLayer::OnDetach()
{
}

void BoidWorldLayer::OnUpdate()
{
	// Update
	CameraMovement();

	update_timer_ += Time::delta_time_f();
	if (update_timer_ >= 0.1f) {
		flock.flocking();
		update_timer_ = 0.0f;
	}
	

	// Render
	// Clears the background color
	Grout::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	Grout::RenderCommand::Clear();

	Renderer::BeginScene(*camera_);

	world_map_.OnRender();

	for (auto& boid : flock.flock)
	{
		boid_object_->transform.set_position(boid.position);
		Grout::Renderer::RenderModelObject(boid_object_, boid_shader_);
	}

	Renderer::EndScene();
}

void BoidWorldLayer::OnImGuiRender()
{
	ImGui::Begin("Settings", &imgui_open);

	ImGui::Checkbox("Camera segue os boids", &camFollowFlock);
	if (camFollowFlock) {
		//camera_->get_transform().set_rotation(glm::lookAt(camera_->get_transform().get_position(), flock.flock_position));
		glm::vec3 new_direction = flock.flock_position - camera_->get_transform().get_position();
		new_direction = glm::normalize(new_direction);
		float dot_X = glm::dot(camera_->get_transform().get_rotation().x, new_direction.x);
		float dot_Y = glm::dot(camera_->get_transform().get_rotation().y, new_direction.y);
		//float dot_Z = glm::dot(camera_->get_transform().get_rotation().z, new_direction.z);
		float angle_X = (acos(dot_X) * 180.0f) / glm::pi<float>();
		float angle_Y = (acos(dot_Y) * 180.0f) / glm::pi<float>();
		//float angle_Z = (acos(dot_Z) * 180.0f) / glm::pi<float>();
		camera_->get_transform().set_rotation(glm::vec3(angle_X, angle_Y, 0.0f));
	}

	ImGui::Text("Modo da Camera:");
	ImGui::Checkbox("##cammode1", &camMode1);
	if (camMode1) {
		camMode2 = false;
		camMode3 = false;
	}
	ImGui::SameLine();
	ImGui::Checkbox("##cammode2", &camMode2);
	if (camMode2) {
		camMode1 = false;
		camMode3 = false;
	}
	ImGui::SameLine();
	ImGui::Checkbox("##cammode3", &camMode3);
	if (camMode3) {
		camMode1 = false;
		camMode2 = false;
	}

	glm::vec3 cam_position = camera_->get_transform().get_position();
	ImGui::InputFloat3("Camera Position", glm::value_ptr(cam_position));
	camera_->get_transform().set_position(cam_position);



	ImGui::Text("Flock Position: %.1f %.1f %.1f", flock.flock_position.x, flock.flock_position.y, flock.flock_position.z);

	ImGui::End();
}

void BoidWorldLayer::OnEvent(Grout::Event& event)
{
}

void BoidWorldLayer::CreateCamera(uint32_t width, uint32_t height)
{
	camera_ = CreateRef<Camera>(glm::vec3(0.0f, 18.2f, 0.0f), width, height);
	Camera::set_main(camera_);
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
