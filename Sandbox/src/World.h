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
	void OnRender();

	void OnImGuiRender();

private:
	void GenerateGround();
private:
	Grout::Ref<Grout::Object> ground_object_;

	Grout::Ref<Grout::Shader> mesh_shader_;

	Grout::Ref<Grout::VertexArray> vertex_array_;
};

