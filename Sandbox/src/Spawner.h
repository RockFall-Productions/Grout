#pragma once

#include "Flock.h"
#include "Boids.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>

// Responsible for spawning Boids in the map
class Spawner {
public:
	void static Spawn(Flock& flock) {
		int offset = 0;

		// Add Leader
		if (flock.flock.size() == 0) {
			glm::vec3 pos = glm::vec3((float(rand() % 100 + 1) / float(100)) * spawn_radius_, float(rand() % 20 + 20), (float(rand() % 100 + 1) / float(100)) * spawn_radius_);
			flock.addBoid(pos, true);
			offset = 1;
		}

		// Add all others
		for (int i = 0; i < spawn_count_ - offset; i++) {
			// Random number position
			glm::vec3 pos =  glm::vec3((float(rand() % 100+1)/float(100)) * spawn_radius_, float(rand() % 20 + 20),(float(rand() % 100 + 1) / float(100)) * spawn_radius_);
			flock.addBoid(pos);
		}
	}

	void static RemoveRandomBoid(Flock& flock, int count) {
		for (int i = 0; i < count; i++) {
			// Random number position
			if (flock.flock.size() != 0)
				flock.removeBoid();
		}
	}

	void static OnImGuiRender(Flock& flock) {
		ImGui::Text("Boids Spawn");
		ImGui::Text("Total Boids on Flock: %d", flock.flock.size());
		ImGui::SliderFloat("Spawn radius", &spawn_radius_, 5.0f, 50.0f);
		ImGui::SliderInt("Spawn count", &spawn_count_, 0, 100);

		bool button_cb = ImGui::Button("Spawn!");
		if (button_cb) {
			Spawn(flock);
		}

		ImGui::SliderInt("Kill count", &kill_count, 0, flock.flock.size());
		button_cb = ImGui::Button("Kill!");
		if (button_cb) {
			RemoveRandomBoid(flock, kill_count);
		}
	}
private:
	static int kill_count;
	static int spawn_count_;
	static float spawn_radius_;
};