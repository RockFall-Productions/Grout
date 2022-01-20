#pragma once

#include "Grout/Core/Core.h"

namespace Grout {
	class Shader {
	public:
		virtual ~Shader() = default;

		// Activates the Shader Program
		virtual void Bind() const = 0;
		// Deactivates the Shader Program
		virtual void Unbind() const = 0;

		static Shader* Create(const char* vertex_code, const char* fragment_code, const char* geometry_code = nullptr);
	};
}