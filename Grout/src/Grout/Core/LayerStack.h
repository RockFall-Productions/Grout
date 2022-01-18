#pragma once

#include "Grout/Core/Core.h"
#include "Grout/Core/Layer.h"

#include <vector>

namespace Grout {
	class  LayerStack
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
		int layer_insert_index_;
	};
}

