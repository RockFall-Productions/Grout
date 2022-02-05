#pragma once

#include <Grout.h>

#include <glm/glm.hpp>

class World
{
public:
	struct TerrainData {
		// World position on the Y axis
		float y_position = 0.0f;

		// Lowest possible Y value
		float lowest_height = -14.0f;

		//float height_bottom_cutoff;
		//float height_top_cutoff;

		// Distance from lowest Y to highest
		float highest_height = 48.0f;
		// How much, into the possible altitude range, colours should spread over. 
		// High spread values means extreme colours won't show
		float spread = 0.55f;

		std::vector<glm::vec4> biome_colours = { glm::vec4(0.51f, 0.57f, 0.46f, 1.0f),
												 glm::vec4(0.75f, 0.80f, 0.69f, 1.0f),
												 glm::vec4(0.76f, 0.89f, 0.72f, 1.0f) };
		//std::vector<glm::vec4> biome_colours = { glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		//										 glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		//										 glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) };

		// part = 1.0f / (biome_colours.size() - 1)
		float part = 0.5f;

		////////////    Noise attributes   ////////////
		//float noise_amplitude = 10;
		float persistance = 0.38f;
		float lacunarity = 4.3f;
		int octaves = 3;
		float roughness = 0.35f;
	};

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
	glm::vec4 CalculateColours(float height, float amplitude);
private:
	Grout::Ref<Grout::Object> map_object_;
	Grout::Ref<Grout::Object> skybox_object_;
	Grout::Ref<Grout::Object> ground_object_;

	Grout::Ref<Grout::Shader> map_shader_;
	Grout::Ref<Grout::Shader> skybox_shader_;
	Grout::Ref<Grout::Shader> ground_shader_;

	TerrainData terrain_data_ = TerrainData();

	bool changed = false;
};

