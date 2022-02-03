#include "BoidWorldLayer.h"

#include <glm/glm/gtc/type_ptr.hpp>

#include <imgui/widgets/imGuIZMO/imGuIZMOquat.h>

#include "Spawner.h"

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
	boid_object_->transform.set_scale(glm::vec3(-0.3f, 0.3f, -0.3f));

	//flock.addBoid(glm::vec3(0.0f, 18.2f, -15.0f));

}

void BoidWorldLayer::OnDetach()
{
}

void BoidWorldLayer::OnUpdate()
{
	// Update
	if (camFlyMode) {
		CameraMovement();
	}

	flock.flocking();

	// Render
	// Clears the background color
	Grout::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	Grout::RenderCommand::Clear();

	Renderer::BeginScene(*camera_);

	world_map_.OnRender(light_data_);

	for (auto& boid : flock.flock)
	{
		if (boid.leader)
			boid_object_->transform.set_scale(glm::vec3(-0.5f, 0.5f, -0.5f));
		boid_object_->transform.set_position(boid.position);
		boid_object_->transform.look_at(boid.position + boid.velocity);
		Grout::Renderer::RenderModelObject(boid_object_, boid_shader_, light_data_);
		if (boid.leader)
			boid_object_->transform.set_scale(glm::vec3(-0.3f, 0.3f, -0.3f));
	}

	//boid_object_->transform.set_position(glm::vec3(0.0f, 30.3f, -6.0f));
	//boid_object_->transform.look_at(camera_->get_transform()().get_position());
	//Grout::Renderer::RenderModelObject(boid_object_, boid_shader_);

	Renderer::EndScene();
}

void BoidWorldLayer::OnImGuiRender()
{
	ImGui::Begin("Settings", &imgui_open);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Lightning");
	ImGui::DragFloat3("Light Source Position", glm::value_ptr(light_data_.light_pos));
	ImGui::Spacing();
	ImGui::ColorEdit3("Ambient Light", glm::value_ptr(light_data_.ambient_light));
	ImGui::SliderFloat("Ambient Light Strength", &light_data_.ambient_light_strength, 0.0f, 1.0f);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Camera Settings");
	ImGui::Spacing();
	ImGui::Text("Rotation");

	ImGui::gizmo3D("##gizmo1", quat(camera_->get_transform().get_orientation()) /*, size,  mode */);
	ImGui::Spacing();
	glm::vec3 cam_position = camera_->get_transform().get_position();
	ImGui::InputFloat3("Camera Position", glm::value_ptr(cam_position));
	ImGui::SliderFloat("Camera Speed", &cam_speed_, 0.0f, 30.0f);

	ImGui::Checkbox("Camera segue os boids", &camFollowFlock);
	if (camFollowFlock) {
		camFollowLeader = false;
		if (flock.flock.size() > 0) {
			camera_->set_target(flock.flock_position);
			camera_->LookAtTarget();
		}
	}
	ImGui::Checkbox("Camera segue o lider", &camFollowLeader);
	if (camFollowLeader) {
		camFollowFlock = false;
		if (flock.flock.size() > 0) {
			camera_->set_target(flock.flock[0].position);
			camera_->LookAtTarget();
		}
	}

	ImGui::SliderFloat("Camera Superior Vision Offset", &cam_superior_offset_, 10.0f, 140.0f);

	ImGui::Text("Modo da Camera:");
	ImGui::Checkbox("Torre", &camMode1);
	if (camMode1) {
		camera_->get_transform().set_position(glm::vec3(0.0f, 30.2f, 0.0f));
		camMode2 = false;
		camMode3 = false;
		camFlyMode = false;
	}
	ImGui::SameLine();
	ImGui::Checkbox("Seguir boids", &camMode2);
	if (camMode2) {
		//camera_->get_transform().set_position();
		camMode1 = false;
		camMode3 = false;
		camFlyMode = false;
	}

	//ImGui::SliderFloat("Camera Lock Offset", &camera_lock_offset, 0.0f, 3.0f);

	ImGui::Checkbox("Superior", &camMode3);
	if (camMode3) {
		camMode1 = false;
		camMode2 = false;
		camFlyMode = false;

		// Smooth movement
		if (flock.flock.size() != 0 && camFollowFlock) {
			glm::vec2 cam_pos_2d(camera_->get_transform().get_position().x, camera_->get_transform().get_position().z);
			glm::vec2 flock_pos_2d(flock.flock_position.x, flock.flock_position.z);
			if (glm::distance(cam_pos_2d, flock_pos_2d) < camera_lock_offset)
				camera_->get_transform().set_position(flock.flock_position);
			else
				camera_->LerpMoveToTarget(glm::vec3(flock.flock_position.x, camera_->get_transform().get_position().y, flock.flock_position.z), cam_speed_);
		}
		else if (flock.flock.size() != 0 && camFollowLeader){
			glm::vec2 cam_pos_2d(camera_->get_transform().get_position().x, camera_->get_transform().get_position().z);
			glm::vec2 flock_pos_2d(flock.flock[0].position.x, flock.flock[0].position.z);
			if (glm::distance(cam_pos_2d, flock_pos_2d) < camera_lock_offset)
				camera_->get_transform().set_position(flock.flock[0].position);
			else
				camera_->LerpMoveToTarget(glm::vec3(flock.flock[0].position.x, camera_->get_transform().get_position().y, flock.flock[0].position.z), cam_speed_);
		}
		else 
			camera_->get_transform().set_position(glm::vec3(camera_->get_transform().get_position().x, flock.get_settings().maxHeight + cam_superior_offset_, camera_->get_transform().get_position().z));
		// Correcting Y axis
		camera_->get_transform().set_position(glm::vec3(camera_->get_transform().get_position().x, 30.0f + cam_superior_offset_, camera_->get_transform().get_position().z));
		// Look down
		glm::vec3 look_position = glm::vec3(camera_->get_transform().get_position().x + (0.01f * cam_superior_offset_), 0.0f, camera_->get_transform().get_position().z + (0.01f * cam_superior_offset_));
		camera_->get_transform().look_at(look_position);

	}
	ImGui::SameLine();
	ImGui::Checkbox("Vôo Livre", &camFlyMode);
	if (camFlyMode) {
		camera_->get_transform().set_position(cam_position);
		camMode1 = false;
		camMode2 = false;
		camMode3 = false;
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Flock Position: %.1f %.1f %.1f", flock.flock_position.x, flock.flock_position.y, flock.flock_position.z);
	ImGui::Spacing();
	flock.OnImGuiRender();
	Spawner::OnImGuiRender(flock);

	ImGui::End();
}

void BoidWorldLayer::OnEvent(Grout::Event& event)
{
	//Grout::EventDispatcher dispatcher(event);
	//dispatcher.Dispatch<Grout::MouseMovedEvent>(GRT_BIND_EVENT_FN(BoidWorldLayer::OnMouseMovedEvent));
}

bool BoidWorldLayer::OnMouseMovedEvent(Grout::MouseMovedEvent event)
{


	return false;
}

void BoidWorldLayer::CreateCamera(uint32_t width, uint32_t height)
{
	camera_ = CreateRef<Camera>(glm::vec3(0.0f, 30.2f, 0.0f), width, height);
	Camera::set_main(camera_);
}

void BoidWorldLayer::CameraMovement()
{
	// Get mouse movement
	const glm::vec2& mouse{ Input::get_mouse_x(), Input::get_mouse_y() };
	glm::vec2 delta = (mouse - last_mouse_position_) * 0.003f;
	last_mouse_position_ = mouse;
	// Rotate the camera
	float yawSign = camera_->get_transform().get_up_direction().y < 0 ? -1.0f : 1.0f;
	camera_->get_transform().add_yaw(yawSign * delta.x * camera_fly_rotation_speed_);
	camera_->get_transform().add_pitch(delta.y * camera_fly_rotation_speed_);

	// Move left and right
	if (Grout::Input::is_key_pressed(GRT_KEY_W)) {
		camera_->get_transform().add_position(camera_->get_transform().get_forward_direction() * Grout::Time::delta_time_f() * camera_fly_speed_);
		GRT_TRACE("W is pressed");
	}

	else if (Grout::Input::is_key_pressed(GRT_KEY_S))
		camera_->get_transform().add_position(camera_->get_transform().get_forward_direction() * -1.0f * Grout::Time::delta_time_f() * camera_fly_speed_);

	// Move Forward and Backward
	if (Grout::Input::is_key_pressed(GRT_KEY_D))
		camera_->get_transform().add_position(camera_->get_transform().get_right_direction() * Grout::Time::delta_time_f() * camera_fly_speed_);

	else if (Grout::Input::is_key_pressed(GRT_KEY_A))
		camera_->get_transform().add_position(camera_->get_transform().get_right_direction() * -1.0f * Grout::Time::delta_time_f() * camera_fly_speed_);


}
