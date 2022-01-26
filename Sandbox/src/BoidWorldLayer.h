#pragma once

#include "Grout.h"

#include "World.h"

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
	Grout::Scope<Grout::Camera> camera_;
	World world_map_;

	std::vector<Grout::Ref<Grout::Object>> cubes_;
	Grout::Ref<Grout::Shader> shader_;
	Grout::Ref<Grout::VertexArray> vertex_array_;
};

