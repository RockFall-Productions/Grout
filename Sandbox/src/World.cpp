#include "World.h"

using namespace Grout;

void World::Start()
{
	//mesh_shader_ = Renderer::FindShaderByName("Mesh");
	mesh_shader_.reset(Grout::Shader::Create("assets/shaders/mesh.glsl"));

	// Create Ground and Tower
	//GenerateGround();
}

void World::OnUpdate()
{

}

void World::OnRender()
{
	// Render the ground and tower
	
	Renderer::RenderMeshObject(ground_object_, mesh_shader_);

	//glm::mat4 transform = ground_object_->transform.get_transform();
	//Renderer::Submit(mesh_shader_, ground_object_->mesh_component.vertex_array, transform);
}

void World::OnImGuiRender()
{

}

void World::GenerateGround()
{

	std::array<float, (20 * 20 * 7)> vertices;

	int x_size = 20;
	int z_size = 20;

	int i = 0;
	for (int z = 0; z < z_size; z++)
	{
		for (int x = 0; x < x_size; x++)
		{
			vertices[i] = x;
			vertices[i+1] = 0;
			vertices[i+2] = z;

			vertices[i + 3] = 0.3f;
			vertices[i + 4] = 0.2f;
			vertices[i + 5] = 0.5f;
			vertices[i + 6] = 1.0f;
			// TODO: add other data to each vertice
			
			i += 7;
		}
	}

	std::array<uint32_t, (20 * 20 * 6)> indices;

	int vert = 0;
	int triang = 0;
	for (int z = 0; z < z_size; z++)
	{
		for (int x = 0; x < x_size; x++)
		{
			indices[triang + 0] = vert + 0;
			indices[triang + 1] = vert + 1;
			indices[triang + 2] = vert + x_size + 1;
			indices[triang + 3] = vert + x_size + 1;
			indices[triang + 4] = vert + x_size;
			indices[triang + 5] = vert + 0;

			++vert;
			triang += 6;
		}
	}

	Grout::BufferLayout layout = {
			{Grout::ShaderDataType::Float3, "a_position"},
			{Grout::ShaderDataType::Float4, "a_color" }
	};
	
	ground_object_ = CreateRef<Object>("World Ground", glm::vec3(-10.0f, 0.0f, -20.0f));
	ground_object_->mesh_component = MeshComponent(vertices.data(), sizeof(vertices), indices.data(), sizeof(indices), layout);

}
