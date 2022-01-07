#include <Grout.h>

#include "imgui/imgui.h"

class TestLayer : public Grout::Layer {
public:
	TestLayer()
		: Layer("Testing") {}

	void OnUpdate() override {
		if (Grout::Input::is_key_pressed(GRT_KEY_W))
			GRT_CORE_TRACE("Pressing 'W': {0}", Grout::Input::is_key_pressed(87));
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello, is anybody in there?");
		ImGui::End();
	}

	void OnEvent(Grout::Event& event) override {
		//GRT_TRACE("{0}", event);
	}
};

class Sandbox : public Grout::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {

	}
};

Grout::Application* Grout::CreateApplication() {
	return new Sandbox();
}