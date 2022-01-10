#pragma once

#include "Grout/Core.h"

// GLM
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

namespace Grout {
	class Shader {
	public:
		//  -- Constructors --
		Shader() : ID(0) { }
		Shader(const char* vertex_file, const char* fragment_file, const char* geometry_file = nullptr);
		~Shader();

		void LoadShaderFiles(const char* vertex_file, const char* fragment_file, const char* geometry_file = nullptr);
		
		// Compiles and link given vertex, fragment and (optional) geometry shaders, 
		// and stores the created shaderProgram ID's into class's variable
		void CompileNLink(const char* vertex_code, const char* fragment_code, const char* geometry_code = nullptr);

		// Activates the Shader Program
		Shader& Activate();
		// Deactivates the Shader Program
		void Deactivate();

		// Deletes the Shader Program
		void Delete();

		// Sets for Uniform shader variables
		void SetFloat(const char* name, float value, bool useShader = false);
		void SetInteger(const char* name, int value, bool useShader = false);
		void SetVector2f(const char* name, float x, float y, bool use_shader = false);
		void SetVector2f(const char* name, const glm::vec2& value, bool use_shader = false);
		void SetVector3f(const char* name, float x, float y, float z, bool use_shader = false);
		void SetVector3f(const char* name, const glm::vec3& value, bool use_shader = false);
		void SetVector4f(const char* name, float x, float y, float z, float w, bool use_shader = false);
		void SetVector4f(const char* name, const glm::vec4& value, bool use_shader = false);
		void SetMatrix4(const char* name, const glm::mat4& matrix, bool use_shader = false);
	private:
		// Checks for error on compilation or linking of shaders and prints them
		void checkCompileErrors(uint32_t shader, const char* type);

		// Get all the contents of a given file
		std::string GetFileContents(const char* file_path);
	private:
		// Reference ID of the Shader Program
		uint32_t ID;
	};
}