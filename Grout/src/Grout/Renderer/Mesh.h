#pragma once

#include "Shader.h"

#include <glm/glm.hpp>

namespace Grout {

    // TODO: Abstract to OpenGLMesh
	class Mesh {
	public:
        struct Vertex {
            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec2 TexCoords;
        };

        struct Texture {
            uint32_t id;
            std::string type;
        };

        // mesh data
        std::vector<Vertex>     vertices;
        std::vector<uint32_t>   indices;
        std::vector<Texture>    textures;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures);
        void Render(const Ref<Shader>& shader);

    private:
        void SetupMesh();
    private:

	};

    class Model
    {
    public:
        Model(char* path)
        {
            LoadModel(path);
        }
        void Render(const Ref<Shader>& shader);
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Mesh::Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
            std::string typeName);
    };
}