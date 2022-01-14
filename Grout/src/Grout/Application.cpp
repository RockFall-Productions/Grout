#include "grtpch.h"
#include "Application.h"

#include "Grout/Log.h"

#include "Grout/Renderer/Renderer.h"

#include "Grout/Input.h"

namespace Grout {
	// Singleton
	// TODO implement it in a correct singleton way
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	Application* Application::instance_ = nullptr;


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

		// Creation of Vertex Array
		vertex_array_.reset(VertexArray::Create());

		float vertices[4 * 7] = {
			// Position --- Color
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> vertex_buffer;
		// Creation of Vertex Buffer
		vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		// Setting the Vertex Buffer Layout
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_position"},
			{ ShaderDataType::Float4, "a_color"}
		};
		vertex_buffer->set_layout(layout);
		// Adding this VertexBuffer to the VertexArray
		vertex_array_->AddVertexBuffer(vertex_buffer);

		// Setting up the Index Buffer and adding it to the VertexArray
		uint32_t indices[] = { 0, 1, 2};
		std::shared_ptr<IndexBuffer> index_buffer;
		index_buffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertex_array_->SetIndexBuffer(index_buffer);

		square_VA_.reset(VertexArray::Create());
		float vertices2[4 * 3] = {
			// Position --- Color
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVB->set_layout({ { ShaderDataType::Float3, "a_position"} });

		square_VA_->AddVertexBuffer(squareVB);

		uint32_t indices2[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		square_VA_->SetIndexBuffer(squareIB);


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

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;

			out vec3 v_position;

			void main() {
				v_position = a_position;
				gl_Position = vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main() {
				color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
			}
		)";

		shader_.reset(new Shader());
		shader_->CompileAndLink(vertexSrc2.c_str(), fragmentSrc2.c_str());
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
			// Clears the background color
			RenderCommand::SetClearColor({1.0f, 0.0f, 1.0f, 1.0f});
			RenderCommand::Clear();

			// 
			Renderer::BeginScene();

			shader_->Bind();
			Renderer::Submit(square_VA_);

			Renderer::EndScene();
			// To-do: Threads
			//Renderer::Flush();

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
