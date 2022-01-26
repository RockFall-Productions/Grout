#pragma once

#include "Grout/Renderer/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtx/quaternion.hpp>

namespace Grout {


	struct CubeRendererComponent {

		/*
		float vertices[6 * 6 * 7] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.4f, 0.3f, 0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.4f, 0.3f, 0.5f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.4f, 0.2f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.4f, 0.2f, 1.0f
		};
		*/

		float vertices[5 * 6 * 6] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		uint32_t indices[36] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
								  11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
								  21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
								  31, 32, 33, 34, 35 };

	};

	struct MeshComponent {
		MeshComponent() : vertex_array() { }

		MeshComponent(std::vector<float> vertices, std::vector<uint32_t> indices, BufferLayout layout) {

			Ref<VertexBuffer> vertex_buffer;
			vertex_buffer.reset(VertexBuffer::Create(vertices.data(), sizeof(*vertices.data())));
			vertex_buffer->set_layout(layout);
			
			vertex_array.reset(VertexArray::Create());
			vertex_array->AddVertexBuffer(vertex_buffer);

			Grout::Ref<IndexBuffer> index_buffer;
			index_buffer.reset(IndexBuffer::Create(indices.data(), sizeof(*indices.data()) / sizeof(uint32_t)));
			
			vertex_array->SetIndexBuffer(index_buffer);
		}

		MeshComponent(float* vertices, uint32_t size_v, uint32_t* indices, uint32_t size_i, BufferLayout layout) {

			Ref<VertexBuffer> vertex_buffer;
			vertex_buffer.reset(VertexBuffer::Create(vertices, size_v));
			vertex_buffer->set_layout(layout);

			vertex_array.reset(VertexArray::Create());
			vertex_array->AddVertexBuffer(vertex_buffer);

			Grout::Ref<IndexBuffer> index_buffer;
			index_buffer.reset(IndexBuffer::Create(indices, size_i / sizeof(uint32_t)));

			vertex_array->SetIndexBuffer(index_buffer);
		}

		Ref<VertexArray> vertex_array;
	};

}