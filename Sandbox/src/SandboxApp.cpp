#include <Grout.h>

class TestLayer : public Grout::Layer {
public:
	TestLayer()
		: Layer("Testing") {}

	void OnUpdate() override {
		GRT_INFO("TestLayer::Update");
	}

	void OnEvent(Grout::Event& event) override {
		GRT_TRACE("{0}", event);
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