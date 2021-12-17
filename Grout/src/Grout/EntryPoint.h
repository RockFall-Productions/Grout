#pragma once

#ifdef GRT_PLATAFORM_WINDOWS

extern Grout::Application* Grout::CreateApplication();

int main(int argc, char** argv) {
	auto app = Grout::CreateApplication();
	app->Run();
	delete app;
}

#endif