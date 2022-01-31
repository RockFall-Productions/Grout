#include "World.h"

#include "Grout/Utils/PerlimNoise.h"
#include "Plataform/OpenGL/OpenGLShader.h"

using namespace Grout;

void World::Start()
{
	// Create Ground and Tower
	//GenerateGround();

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
}

void World::OnUpdate()
{

}

void World::OnRender()
{
	// Render the ground and tower
	Renderer::RenderModelObject(map_object_, map_shader_);

	// Render Skybox
	Renderer::RenderSkybox(skybox_object_, Camera::get_main(), skybox_shader_);
}

void World::OnImGuiRender()
{

}

void World::GenerateGround()
{
	size_t x_size = 20;
	size_t z_size = 20;

	std::vector<float> vertices(x_size * z_size * 7, 0);

	size_t i = 0;
	for (int z = 0; z < z_size; z++)
	{
		for (int x = 0; x < x_size; x++)
		{
			vertices[i] = float(x);
			vertices[i + 1] = 0.0f;
			vertices[i + 2] = float(z);

			vertices[i + 3] = 0.3f;
			vertices[i + 4] = 0.2f;
			vertices[i + 5] = 0.5f;
			vertices[i + 6] = 1.0f;
			// TODO: add other data to each vertice
			
			i += 7;
		}
	}

	std::vector<uint32_t> indices(x_size * z_size * 6, 0);

	size_t vert = 0;
	size_t triang = 0;
	for (int z = 0; z < z_size; z++)
	{
		for (int x = 0; x < x_size; x++)
		{
			indices[triang + 0] = vert + 0;			// bottom left
			indices[triang + 1] = vert + 1;			// bottom right
			indices[triang + 2] = vert + x_size + 1;// top right
			indices[triang + 3] = vert + x_size + 1;// top right
			indices[triang + 4] = vert + x_size;	// top left
			indices[triang + 5] = vert + 0;			// bottom left

			++vert;
			triang += 6;
		}
	}

	Grout::BufferLayout layout = {
			{Grout::ShaderDataType::Float3, "a_position"},
			{Grout::ShaderDataType::Float4, "a_color" }
	};
	
	///ground_object_ = CreateRef<Object>("World Ground", glm::vec3(-10.0f, 0.0f, -20.0f));
	//ground_object_->mesh_component = MeshComponent(&vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size(), layout);

}
