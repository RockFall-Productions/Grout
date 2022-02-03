#include "World.h"

#include "Grout/Utils/PerlimNoise.h"
#include "Plataform/OpenGL/OpenGLShader.h"

#include "third-part/FastNoiseLite.h"

using namespace Grout;

void World::Start()
{
	// Create Skybox
	skybox_shader_.reset(Grout::Shader::Create("assets/shaders/skybox.glsl"));
	std::dynamic_pointer_cast<Grout::OpenGLShader>(skybox_shader_)->uniform_set_integer("u_skybox", 0, true);
	skybox_object_ = CreateRef<Object>("SkyBox", glm::vec3(0.0f));
	skybox_object_->skybox_component = CreateRef<SkyBoxComponent>();

	// Create Map
	map_object_ = Grout::CreateRef<Grout::Object>("Tower and Ground", glm::vec3(0.0f, 0.0f, 0.0f));
	map_object_->model_3D = Grout::CreateRef<Grout::Model>("assets/objects/tower/tower_with_ground.obj");
	map_object_->transform.set_scale(glm::vec3(0.3f));
	map_shader_.reset(Grout::Shader::Create("assets/shaders/model.glsl"));

	// Create Ground
	GenerateGround();
	ground_shader_.reset(Grout::Shader::Create("assets/shaders/low_poly_mesh.glsl"));
}

void World::OnUpdate()
{

}

void World::OnRender(Grout::Renderer::LightData light_data)
{
	// Render the ground and tower
	Renderer::RenderModelObject(map_object_, map_shader_, light_data);

	// Render Skybox
	Renderer::RenderSkybox(skybox_object_, Camera::get_main(), skybox_shader_);

	// Render Ground
	Renderer::RenderMeshObject(ground_object_, ground_shader_, light_data);
}

void World::OnImGuiRender()
{

}

void World::GenerateGround()
{
	// Create and configure FastNoise object
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);


	size_t x_size = 100;
	size_t z_size = 100;

	std::vector<float> vertices(x_size * z_size * 7, 0);

	size_t i = 0;
	for (int z = 0; z < z_size; z++)
	{
		for (int x = 0; x < x_size; x++)
		{
			vertices[i] = float(x);
			vertices[i + 1] = noise.GetNoise((float)x, (float)z);
			vertices[i + 2] = float(z);

			vertices[i + 3] = 0.5f;
			//vertices[i + 4] = (noise.GetNoise((float)x, (float)z) + 1) / 2.0f;
			vertices[i + 4] = 1.0f;
			vertices[i + 5] = 0.5f;
			vertices[i + 6] = 1.0f;
			// TODO: add other data to each vertice
			
			i += 7;
		}
	}

	//std::vector<uint32_t> indices(((z_size -1) * (2 * (x_size-1))) * 3, 0);
	//std::vector<uint32_t> indices(z_size * x_size * 6, 0);
	std::vector<uint32_t> indices;

	size_t vert = 0;
	size_t triang = 0;
	for (int z = 0; z < z_size-1; z++)
	{
		for (int x = 0; x < x_size-1; x++)
		{
			//indices[triang + 0] = vert + 0;				// bottom left
			//indices[triang + 1] = vert + 1;				// bottom right
			//indices[triang + 2] = vert + x_size;		// top left
			//indices[triang + 3] = vert + x_size;		// top left
			//indices[triang + 4] = vert + 1;				// bottom right
			//indices[triang + 5] = vert + x_size + 1;	// top right
			indices.push_back(vert + 0);			// bottom left
			indices.push_back(vert + 1);			// bottom right
			indices.push_back(vert + x_size);		// top left
			indices.push_back(vert + x_size);		// top left
			indices.push_back(vert + 1);			// bottom right
			indices.push_back(vert + x_size + 1);	// top right

			++vert;
			triang += 6;
		}
	}

	Grout::BufferLayout layout = {
			{Grout::ShaderDataType::Float3, "a_position"},
			{Grout::ShaderDataType::Float4, "a_color" }
	};
	
	ground_object_ = CreateRef<Object>("World Ground", glm::vec3((x_size * -1.0f) / 2.0f, 26.2f, (z_size * -1.0f) / 2.0f));
	ground_object_->mesh_component = MeshComponent(&vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size(), layout);


}
