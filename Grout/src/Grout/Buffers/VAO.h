#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"

// Holds the VAO ID and performs all need actions
namespace Grout {
	class VAO {
	public:
		// Reference ID of the VAO
		GLuint ID;

		// Creates one VAO object and stores it's ID into class variable
		VAO();

		// Inserts the given VBO into this VAO
		// 'VBO'			: instance of the VBO to be inserted
		// 'layout'			: index where it will be inserted on the VAO
		// 'numComponents'	: specifies the number of components on the attribute and 
		//						must be 1, 2, 3, 4, or GL_BGRA. 
		// 'type'			: specifies the data type of each component
		// 'stride'			: specifies the byte stride from one attribute to the 
		//						next, allowing vertices and attributes to be packed 
		//						into a single array or stored in separate arrays.
		// 'offset'			: in bytes, where the attribute starts
		//
		//			 i.e.: a layout 1, size 3, offset 3*sizeof(flloat) 
		//			 and stride of 6*sizeof(flloat) for a {X,Y,Z,R,G,B} 
		//			 vertice, can select only the RGB part
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		void Bind();
		void Unbind();
		void Delete();
	};
}