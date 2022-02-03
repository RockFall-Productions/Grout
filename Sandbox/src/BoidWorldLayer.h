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
	bool OnMouseMovedEvent(Grout::MouseMovedEvent event);

private:
	void CreateCamera(uint32_t width, uint32_t height);

	void CameraMovement();

private:
	Grout::Ref<Grout::Camera> camera_;
	World world_map_;

	Grout::Ref<Grout::Shader> boid_shader_;
	Grout::Ref<Grout::Object> boid_object_;

	Flock flock;

	float update_timer_ = 0;

	// IM GUI
	bool imgui_open = true;

	// Camera
	float cam_speed_ = 30.0f;
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
	float camera_fly_speed_ = 16.0f;
};

