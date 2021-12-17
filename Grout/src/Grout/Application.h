#pragma once

#include "Core.h"

namespace Grout {
	class GROUT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

