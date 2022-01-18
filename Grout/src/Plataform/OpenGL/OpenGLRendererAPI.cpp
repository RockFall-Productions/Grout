#include "grtpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Grout {
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array)
	{
		vertex_array->Bind();
		//glDrawElements(GL_TRIANGLES, vertex_array->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}