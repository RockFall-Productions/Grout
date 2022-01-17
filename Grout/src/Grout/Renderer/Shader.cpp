#include "grtpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Grout {
	Shader::~Shader()
	{
		Delete();
	}
	Shader::Shader(const char* vertex_file, const char* fragment_file, const char* geometry_file) : id_(0)
	{
		LoadShaderFiles(vertex_file, fragment_file, geometry_file);
	}

	void Shader::LoadShaderFiles(const char* vertex_file, const char* fragment_file, const char* geometry_file)
	{
		// Getting shader codes from files
		std::string vertex_code = GetFileContents(vertex_file);
		std::string fragment_code = GetFileContents(fragment_file);

		// Deals with geometry shader, if given
		std::string geometry_code;
		if (geometry_file != nullptr) {
			geometry_code = GetFileContents(geometry_file);
		}

		CompileAndLink(vertex_code.c_str(), fragment_code.c_str(), geometry_code.c_str());
		
	}

	std::string Shader::GetFileContents(const char* file_path) {

		std::ifstream in(file_path, std::ios::binary);
		if (in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return (contents);
		}

		GRT_CORE_ERROR("Shader file (\"{0}\") not found in Shader::GetFileContents", file_path);
		GRT_ASSERT(false, "Given shader file not found");
	}

	void Shader::CompileAndLink(const char* vertex_code, const char* fragment_code, const char* geometry_code) {
		const GLchar* vertex_source = vertex_code;
		const GLchar* fragment_source = fragment_code;
		const GLchar* geometry_source;
		if (geometry_code != nullptr)
			geometry_source = geometry_code;

		// Vertex Shader - create object and compiles it
		uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_source, NULL);
		glCompileShader(vertex_shader);
		checkCompileErrors(vertex_shader, "VERTEX");

		// Fragment Shader - create object and compiles it
		uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_source, NULL);
		glCompileShader(fragment_shader);
		checkCompileErrors(fragment_shader, "FRAGMENT");

		// Geometry Shader - only creates if file is given
		uint32_t geometry_shader = 0;
		if (geometry_code != nullptr)
		{
			geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry_shader, 1, &geometry_source, NULL);
			glCompileShader(geometry_shader);
			checkCompileErrors(geometry_shader, "GEOMETRY");
		}

		// Shader Program - creation and linking of compiled shaders
		this->id_ = glCreateProgram();
		glAttachShader(this->id_, vertex_shader);
		glAttachShader(this->id_, fragment_shader);
		if (geometry_code != nullptr)
			glAttachShader(this->id_, geometry_shader);
		glLinkProgram(this->id_);
		checkCompileErrors(this->id_, "PROGRAM");

		glDetachShader(id_, vertex_shader);
		glDetachShader(id_, fragment_shader);
		if (geometry_code != nullptr)
			glDetachShader(id_, geometry_shader);

		// Cleans already stored objects
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		if (geometry_code != nullptr)
			glDeleteShader(geometry_shader);
	}

	Shader& Shader::Bind() {
		glUseProgram(this->id_);
		return *this;
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::Delete() {
		glDeleteProgram(id_);
	}

	void Shader::checkCompileErrors(uint32_t shader, const char* type)
	{
		// Error code from:
		//	https://www.khronos.org/opengl/wiki/Shader_Compilation
		//	https://learnopengl.com/Getting-started/Hello-Triangle
		GLint success;
		char info_log[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				GRT_CORE_ERROR("{0} SHADER: Compilation failure!", type);
				GRT_CORE_TRACE("{0}", info_log);
				GRT_ASSERT(false, "Shader Compilation Error");
			}
			else {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
			}
		}
		else {
			glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE) {
				glGetProgramInfoLog(shader, 1024, NULL, info_log);
				GRT_CORE_ERROR("SHADER PROGRAM: Linking failure!");
				GRT_CORE_TRACE("{0}", info_log);
				GRT_ASSERT(false, "Shader Linking Error");
			}
		}
	}

	// ------------------------ UNIFORM SETTER ------------------------
	void Shader::uniform_set_float(const char* name, float value, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform1f(glGetUniformLocation(this->id_, name), value);
	}
	void Shader::uniform_set_integer(const char* name, int value, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform1i(glGetUniformLocation(this->id_, name), value);
	}
	void Shader::uniform_set_vector2f(const char* name, float x, float y, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform2f(glGetUniformLocation(this->id_, name), x, y);
	}
	void Shader::uniform_set_vector2f(const char* name, const glm::vec2& value, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform2f(glGetUniformLocation(this->id_, name), value.x, value.y);
	}
	void Shader::uniform_set_vector3f(const char* name, float x, float y, float z, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform3f(glGetUniformLocation(this->id_, name), x, y, z);
	}
	void Shader::uniform_set_vector3f(const char* name, const glm::vec3& value, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform3f(glGetUniformLocation(this->id_, name), value.x, value.y, value.z);
	}
	void Shader::uniform_set_vector4f(const char* name, float x, float y, float z, float w, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform4f(glGetUniformLocation(this->id_, name), x, y, z, w);
	}
	void Shader::uniform_set_vector4f(const char* name, const glm::vec4& value, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniform4f(glGetUniformLocation(this->id_, name), value.x, value.y, value.z, value.w);
	}
	void Shader::uniform_set_matrix4(const char* name, const glm::mat4& matrix, bool use_shader)
	{
		if (use_shader)
			this->Bind();
		glUniformMatrix4fv(glGetUniformLocation(this->id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}