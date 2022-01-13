#include "grtpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Grout/Input.h"

namespace Grout {
	// Singleton
	// TODO implement it in a correct singleton way
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	Application* Application::instance_ = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Grout::ShaderDataType::None:	return GL_NONE;
		case Grout::ShaderDataType::Float:	return GL_FLOAT;
		case Grout::ShaderDataType::Float2:	return GL_FLOAT;
		case Grout::ShaderDataType::Float3:	return GL_FLOAT;
		case Grout::ShaderDataType::Float4:	return GL_FLOAT;
		case Grout::ShaderDataType::Int:	return GL_INT;
		case Grout::ShaderDataType::Int2:	return GL_INT;
		case Grout::ShaderDataType::Int3:	return GL_INT;
		case Grout::ShaderDataType::Int4:	return GL_INT;
		case Grout::ShaderDataType::Mat3:	return GL_FLOAT;
		case Grout::ShaderDataType::Mat4:	return GL_FLOAT;
		case Grout::ShaderDataType::Bool:	return GL_BOOL;
		}

		GRT_CORE_ASSERT(false, "ShaderDataTypeToOpenGLBaseType - The given type {0} is unknown", type);
		return 0;
	}

	Application::Application()
	{
		// Set singleton
		GRT_CORE_ASSERT(!instance_, "Trying to create more than one application");
		instance_ = this;

		// Creating Window and setting the callback
		window_ = std::unique_ptr<Window>(Window::Create());
		window_->set_event_callback(GRT_BIND_EVENT_FN(Application::OnEvent));

		// Creating the ImGui overlay
		imgui_layer_ = new ImGuiLayer;
		layer_stack_.push_overlay(imgui_layer_);
		imgui_layer_->OnAttach();

		// Creating all buffers
		glGenVertexArrays(1, &vertex_array_);
		glBindVertexArray(vertex_array_);

		float vertices[3 * 7] = {
			// Position --- Color
			-0.5f, -0.5f, 0.0f, 0.1f, 1.0f, 0.1f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.4f, 1.0f
		};
		vertex_buffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_position"},
				{ ShaderDataType::Float4, "a_color"}
			};
			vertex_buffer_->set_layout(layout);
		}

		uint32_t index = 0;
		const auto& layout = vertex_buffer_->get_layout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.get_component_count(), 
				ShaderDataTypeToOpenGLBaseType(element.type), 
				element.normalized ? GL_TRUE : GL_FALSE,
				vertex_buffer_->get_layout().get_stride(), 
				(const void*)element.offset
			);
			++index;
		}

		uint32_t indices[] = {
			0, 1, 2
		};
		index_buffer_.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		index_buffer_->Bind();

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			out vec3 v_position;
			out vec4 v_color;

			void main() {
				v_position = a_position;
				v_color = a_color;
				gl_Position = vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_position;
			in vec4 v_color;

			void main() {
				color = v_color;
			}
		)";

		shader_.reset(new Shader());
		shader_->CompileAndLink(vertexSrc.c_str(), fragmentSrc.c_str());
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack_.push_layer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layer_stack_.push_overlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GRT_BIND_EVENT_FN(Application::OnWindowClose));

		// Loops through layer stack from End -> Begin
		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.is_handled()) {
				break;
			}
		}
	}

	void Application::Run() {
		while (running_) {
			glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader_->Activate();
			glBindVertexArray(vertex_array_);
			glDrawElements(GL_TRIANGLES, index_buffer_->get_count(), GL_UNSIGNED_INT, nullptr);

			// Loop through all layers
			for (Layer* layer : layer_stack_) {
				layer->OnUpdate();
 			}

			// ----- ImGui Frame flow -----
			imgui_layer_->BeginFrame();

			for (Layer* layer : layer_stack_) {
				layer->OnImGuiRender();
			}

			imgui_layer_->EndFrame();
			// ----------------------------

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;;
	}
}
