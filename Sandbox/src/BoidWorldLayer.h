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

	bool camFollowFlock = false;
	bool camMode1 = true;
	bool camMode2 = false;
	bool camMode3 = false;
};

