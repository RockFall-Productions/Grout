#pragma once

#include "Transform.h"
#include "Grout/Renderer/Components.h"
#include "Grout/Renderer/Mesh.h"

#include <string>

namespace Grout {
	class Object {
	public:
		Object() { }
		Object(std::string name, glm::vec3 position, glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f));
		~Object() { }

		Transform transform;

		MeshComponent mesh_component = MeshComponent();

		Mesh* mesh = nullptr;

		CubeRendererComponent cube_component = CubeRendererComponent();
	private:
		bool active_in_hierarchy_ = true;
		bool active_ = true;

		std::string name_ = "";
		std::string tag_ = "";

		

		// Layer layer_;
		// Scene scene_;
	};
}