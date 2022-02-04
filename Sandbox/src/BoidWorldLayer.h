#pragma once

#include <Grout.h>

#include "World.h"
#include "Flock.h"

#include "imgui/imgui.h"

class BoidWorldLayer : public Grout::Layer
{
public:
	BoidWorldLayer();
	virtual ~BoidWorldLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Grout::Event& event) override;
private:
	bool OnKeyDownEvent(Grout::KeyPressedEvent event);

private:
	void CreateCamera(uint32_t width, uint32_t height);

	void CameraMovement();

private:
	// Camera
	Grout::Ref<Grout::Camera> camera_;

	// Handles the world (such as the ground, sky, etc)
	World world_map_;

	// Boid prefab
	Grout::Ref<Grout::Shader> boid_shader_;
	Grout::Ref<Grout::Object> boid_object_;

	// Flock controller
	Flock flock;

	// ImGui running (for minimizing)
	bool imgui_open = true;

	// Camera properties (configurable on ImGui)
	float cam_speed_lerp_ = 30.0f;
	float cam_superior_offset_ = 10.0f;
	float camera_lock_offset = 1.0f;
	bool camFollowFlock = false;
	bool camFollowLeader = false;
	bool camMode1 = true;
	bool camMode2 = false;
	bool camMode3 = false;
	bool camFlyMode = false;

	glm::vec2 last_mouse_position_ = {0.0f, 0.0f};
	float camera_fly_rotation_speed_ = 0.8f;
	float camera_fly_speed_ = 30.0f;
	bool lock_fly_ = false;

	Grout::Renderer::LightData light_data_ = Grout::Renderer::LightData();
};

