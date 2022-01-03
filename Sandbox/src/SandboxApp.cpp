#include <Grout.h>

class TestLayer : public Grout::Layer {
public:
	TestLayer()
		: Layer("Testing") {}

	void OnUpdate() override {
		if (Grout::Input::is_key_pressed(GRT_KEY_W))
			GRT_CORE_TRACE("Pressing 'W': {0}", Grout::Input::is_key_pressed(87));
	}

	void OnEvent(Grout::Event& event) override {
		//GRT_TRACE("{0}", event);
	}
};

class Sandbox : public Grout::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
		PushOverlay(new Grout::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Grout::Application* Grout::CreateApplication() {
	return new Sandbox();
}