#pragma once

#include "Grout/Core.h"
#include "Grout/Events/Event.h"

namespace Grout {
	class  Layer {
	public:
		Layer(const std::string& name = "Layer", bool enabled = true);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& get_name() const { return debug_name_;  }
	protected:
		std::string debug_name_;
		bool enabled_;
	};
}

