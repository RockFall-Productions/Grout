#pragma once

#include <Grout.h>

class World
{
public:
	World() {}
	~World() {
		//delete vertices;
		//delete indices;
	}

	void Start();

	void OnUpdate();
	void OnRender(Grout::Renderer::LightData light_data);

	void OnImGuiRender();

private:
	void GenerateGround();
private:
	Grout::Ref<Grout::Object> map_object_;
	Grout::Ref<Grout::Object> skybox_object_;
	Grout::Ref<Grout::Object> ground_object_;

	Grout::Ref<Grout::Shader> map_shader_;
	Grout::Ref<Grout::Shader> skybox_shader_;
	Grout::Ref<Grout::Shader> ground_shader_;

};

