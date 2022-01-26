#pragma once

#include "Grout/Renderer/Shader.h"

#include<glm/glm.hpp>

// TODO: REMOVE!!
typedef unsigned int GLenum;

namespace Grout {
	class OpenGLShader : public Shader {
	public:
		//  -- Constructors --
		OpenGLShader(const char* vertex_file, const char* fragment_file, const char* geometry_file = nullptr);
		OpenGLShader(const std::string& file_path);
		virtual ~OpenGLShader();

		// Activates the Shader Program
		virtual void Bind() const override;
		// Deactivates the Shader Program
		virtual void Unbind() const override;

		// Deletes the Shader Program
		void Delete();

		// Sets for Uniform shader variables
		void uniform_set_float(const char* name, float value, bool useShader = false);
		void uniform_set_integer(const char* name, int value, bool useShader = false);
		void uniform_set_vector2f(const char* name, float x, float y, bool bind_first = false);
		void uniform_set_vector2f(const char* name, const glm::vec2& value, bool bind_first = false);
		void uniform_set_vector3f(const char* name, float x, float y, float z, bool bind_first = false);
		void uniform_set_vector3f(const char* name, const glm::vec3& value, bool bind_first = false);
		void uniform_set_vector4f(const char* name, float x, float y, float z, float w, bool bind_first = false);
		void uniform_set_vector4f(const char* name, const glm::vec4& value, bool bind_first = false);
		void uniform_set_matrix4(const char* name, const glm::mat4& matrix, bool bind_first = false);
	private:
		static GLenum ShaderTypeFromString(std::string& type);

		// Loads the shader from given files
		void LoadShadersFromSingleFile(const std::string& file_path);
		void LoadShaderFiles(const char* vertex_file, const char* fragment_file, const char* geometry_file = nullptr);

		// Get all the contents of a given file
		std::string FileDataToString(const std::string& file_path);
		// Divide the source code into multiple shader sources (vertex, fragment...)
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		// Compiles and link shader codes  into a Shader Program
		void CompileAndLink(const std::unordered_map<GLenum, std::string> shader_sources);
		void CompileAndLink(const char* vertex_code, const char* fragment_code, const char* geometry_code = nullptr);

		// Checks for error on compilation or linking of shaders
		void checkCompileErrors(uint32_t shader, const char* type);
	private:
		// Reference ID of the Shader Program
		uint32_t id_;
	};
}

