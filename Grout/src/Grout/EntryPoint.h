#pragma once

#ifdef GRT_PLATAFORM_WINDOWS

extern Grout::Application* Grout::CreateApplication();

int main(int argc, char** argv) {
	Grout::Log::Init();
	GRT_CORE_WARN("Initialized Log!");
	GRT_ERROR("An error occured!");
	GRT_CRITICAL("CRITICAL ERROR!!! ABORT NOW");

	auto app = Grout::CreateApplication();
	app->Run();
	delete app;
}

#endif