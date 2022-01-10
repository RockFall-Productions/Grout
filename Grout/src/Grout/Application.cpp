#include "grtpch.h"
#include "Application.h"

#include <glad/glad.h>



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

		// Creating the VBO, VAO and EBO buffers
		//VAO vao_ = VAO::VAO();

		GLfloat vertices[] = {
			// Position --- Color
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		GLuint indices[] = {
			0, 1, 2
		};

		//VBO vbo = VBO::VBO(vertices, sizeof(vertices));

		//vao_.Bind();
		// Inserting the VBO into the VAO
		//vao_.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

		//EBO ebo = EBO::EBO(indices, sizeof(indices));

		//vao_.Unbind(); // Must be unbided before the VBO
		//vbo.Unbind();
		//ebo.Unbind();


		shader_.reset(new Shader());
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

			//vao_.Bind();
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			//vao_.Unbind();

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
