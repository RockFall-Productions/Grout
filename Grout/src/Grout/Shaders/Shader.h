#pragma once

#include "Grout/Core.h"
#include <glad/glad.h>

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

// Returns the given file as a string
std::string get_file_contents(const char* filename);

//
class Shader {
public:
	// Reference ID of the Shader Program
	GLuint ID;

	//  -- Empty Constructor --
	Shader() : ID(0) { }

	// -- Constructor --
	// Starts the object and calls CompileNLink( )
	//Shader(const char* vertexFile, const char* fragmentFile, const char* geometrySource = nullptr);

	// Compiles and link given vertex, fragment and (optional) geometry shaders, 
	// and stores the created shaderProgram ID's into class's variable
	void CompileNLink(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	// Activates the Shader Program
	Shader &Activate();
	// Deletes the Shader Program
	void Delete();
	
	// Sets for Uniform shader variables
	void SetFloat(const char* name, float value, bool useShader = false);
	void SetInteger(const char* name, int value, bool useShader = false);
	void SetVector2f(const char* name, float x, float y, bool useShader = false);
	void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
	void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
	void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
	void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
	void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
private:
	// Checks for error on compilation or linking of shaders and prints them
	void checkCompileErrors(GLuint shader, const char* type);
};