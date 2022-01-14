#include "grtpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Grout {
	void Renderer::BeginScene()
	{

	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertex_array)
	{
		RenderCommand::DrawIndexed(vertex_array);
	}
}