#pragma once

#include "Grout/Layer.h"
#include "Grout/Events/MouseEvent.h"
#include "Grout/Events/KeyEvent.h"
#include "Grout/Events/ApplicationEvent.h"

namespace Grout {
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void BeginFrame();
		void EndFrame();
	private:
		float time_ = 0.0f;
	};
}

