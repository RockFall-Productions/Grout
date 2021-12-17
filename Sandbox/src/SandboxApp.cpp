#include <Grout.h>

class Sandbox : public Grout::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Grout::Application* Grout::CreateApplication() {
	return new Sandbox();
}