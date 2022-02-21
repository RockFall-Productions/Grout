#include "grtpch.h"
#include "OpenGLShader.h"

#include<fstream>

#include <glad/glad.h>
#include "Grout/Core/Assert.h"

#include <glm/gtc/type_ptr.hpp>



namespace Grout {

	GLenum OpenGLShader::ShaderTypeFromString(std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		if (type == "geometry")
			return GL_GEOMETRY_SHADER;

		GRT_CORE_ERROR("ShaderTypeFromString: The given type '{0}' is not a valid shader type", type);
		GRT_CORE_ASSERT(false, "Unknown shader type");

		return 0;
	}

	OpenGLShader::OpenGLShader(const char* vertex_file, const char* fragment_file, const char* geometry_file) : id_(0)
	{
		LoadShaderFiles(vertex_file, fragment_file, geometry_file);
	}

	OpenGLShader::OpenGLShader(const std::string& file_path) : id_(0)
	{
		LoadShadersFromSingleFile(file_path);
	}

	OpenGLShader::~OpenGLShader()
	{
		Delete();
	}

	void OpenGLShader::LoadShaderFiles(const char* vertex_file, const char* fragment_file, const char* geometry_file)
	{
		// Getting shader codes from files
		std::string vertex_code = FileDataToString(vertex_file);
		std::string fragment_code = FileDataToString(fragment_file);

		// Deals with geometry shader, if given
		std::string geometry_code;
		if (geometry_file != nullptr) {
			geometry_code = FileDataToString(geometry_file);
		}

		CompileAndLink(vertex_code.c_str(), fragment_code.c_str(), geometry_code.c_str());
	}


	void OpenGLShader::LoadShadersFromSingleFile(const std::string& file_path)
	{
		std::string source = FileDataToString(file_path);
		auto shader_sources = PreProcess(source);

		if (shader_sources.size() == 2)
			CompileAndLink(shader_sources[GL_VERTEX_SHADER].c_str(), shader_sources[GL_FRAGMENT_SHADER].c_str());
		else if (shader_sources.size() == 3)
			CompileAndLink(shader_sources[GL_VERTEX_SHADER].c_str(), shader_sources[GL_FRAGMENT_SHADER].c_str(), shader_sources[GL_GEOMETRY_SHADER].c_str());

	}

	std::string OpenGLShader::FileDataToString(const std::string& file_path) {

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

		GRT_CORE_ERROR("Shader file (\"{0}\") not found in Shader::FileDataToString", file_path);
		GRT_CORE_ASSERT(false, "Given shader file not found");

		return "";
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shader_sources;

		const char* type_token = "#type";
		size_t type_token_length = strlen(type_token);
		size_t pos = source.find(type_token, 0); //Start of shader type declaration line

		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			GRT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + type_token_length + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			GRT_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader #type specified");

			size_t next_line_pos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			GRT_CORE_ASSERT(next_line_pos != std::string::npos, "Syntax error");
			pos = source.find(type_token, next_line_pos); //Start of shader code after shader type declaration line
			shader_sources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(next_line_pos) : source.substr(next_line_pos, pos - next_line_pos);
		}

		return shader_sources;
	}

	// TODO: Divide this method between Compile() and Link()
	void OpenGLShader::CompileAndLink(const char* vertex_code, const char* fragment_code, const char* geometry_code) {
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

	void OpenGLShader::CompileAndLink(const std::unordered_map<GLenum, std::string> shader_sources)
	{
	}

	void OpenGLShader::Bind() const {
		glUseProgram(this->id_);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::Delete() {
		glDeleteProgram(id_);
	}

	void OpenGLShader::checkCompileErrors(uint32_t shader, const char* type)
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
				GRT_CORE_TRACE("{0}\n", info_log);
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
				GRT_CORE_TRACE("{0}\n", info_log);
				GRT_ASSERT(false, "Shader Linking Error");
			}
		}
	}

	// ------------------------ UNIFORM SETTER ------------------------
	void OpenGLShader::uniform_set_float(const char* name, float value, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform1f(glGetUniformLocation(this->id_, name), value);
	}
	void OpenGLShader::uniform_set_bool(const char* name, bool value, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform1i(glGetUniformLocation(this->id_, name), value);
	}
	void OpenGLShader::uniform_set_integer(const char* name, int value, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform1i(glGetUniformLocation(this->id_, name), value);
	}
	void OpenGLShader::uniform_set_vector2f(const char* name, float x, float y, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform2f(glGetUniformLocation(this->id_, name), x, y);
	}
	void OpenGLShader::uniform_set_vector2f(const char* name, const glm::vec2& value, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform2f(glGetUniformLocation(this->id_, name), value.x, value.y);
	}
	void OpenGLShader::uniform_set_vector3f(const char* name, float x, float y, float z, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform3f(glGetUniformLocation(this->id_, name), x, y, z);
	}
	void OpenGLShader::uniform_set_vector3f(const char* name, const glm::vec3& value, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform3f(glGetUniformLocation(this->id_, name), value.x, value.y, value.z);
	}
	void OpenGLShader::uniform_set_vector4f(const char* name, float x, float y, float z, float w, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform4f(glGetUniformLocation(this->id_, name), x, y, z, w);
	}
	void OpenGLShader::uniform_set_vector4f(const char* name, const glm::vec4& value, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniform4f(glGetUniformLocation(this->id_, name), value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::uniform_set_matrix4(const char* name, const glm::mat4& matrix, bool bind_first)
	{
		if (bind_first)
			this->Bind();
		glUniformMatrix4fv(glGetUniformLocation(this->id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}