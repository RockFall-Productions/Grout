#pragma once

#include "Grout/Core.h"
#include "Grout/Layer.h"

#include <vector>

namespace Grout {
	class GROUT_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push_layer(Layer* layer);
		void push_overlay(Layer* overlay);
		void pop_layer(Layer* layer);
		void pop_overlay(Layer* overlay);


		std::vector<Layer*>::iterator begin() { return layers_.begin();  }
		std::vector<Layer*>::iterator end() { return layers_.end();  }
	private:
		// Vector were chosen over an actual stack because
		// we sometimes have to insert things on the middle
		std::vector<Layer*> layers_;
		std::vector<Layer*>::iterator layer_insert_;
	};
}

