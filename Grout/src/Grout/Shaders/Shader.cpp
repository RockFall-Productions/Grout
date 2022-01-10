#include "grtpch.h"
#include "Shader.h"

/* OLD function from when Shader class loaded files
Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometrySource)
{
	CompileNLink(vertexFile, fragmentFile, geometrySource);
}
*/

void Shader::CompileNLink(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	
	// Vertex Shader - create object and compiles it
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	// Fragment Shader - create object and compiles it
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// Geometry Shader - only creates if file is given
	GLuint geometryShader;
	if (geometrySource != nullptr)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometrySource, NULL);
		glCompileShader(geometryShader);
		checkCompileErrors(geometryShader, "GEOMETRY");
	}

	// Shader Program creation and insertion of both objects
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	if (geometrySource != nullptr)
		glAttachShader(this->ID, geometryShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

	// Cleans already stored objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometrySource != nullptr)
		glDeleteShader(geometryShader);
}

Shader &Shader::Activate() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::checkCompileErrors(GLuint shader, const char* type)
{
	// Error code from:
	//	https://www.khronos.org/opengl/wiki/Shader_Compilation
	//	https://learnopengl.com/Getting-started/Hello-Triangle
	GLint success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		}
		else {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		}
	}
}

// ------------------------ UNIFORM SETTER ------------------------
void Shader::SetFloat(const char* name, float value, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const char* name, int value, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader)
		this->Activate();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}