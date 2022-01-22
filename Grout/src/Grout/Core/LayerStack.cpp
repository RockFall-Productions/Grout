#include "grtpch.h"
#include "LayerStack.h"

namespace Grout {
	LayerStack::LayerStack() : layer_insert_index_(0)
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers_) {
			layer->OnDetach();
			delete layer;
		}
	}
	void LayerStack::push_layer(Layer* layer)
	{
		// The layer is emplaced after the last layer and before the first overlay
		layers_.emplace(layers_.begin() + layer_insert_index_, layer);
		layer_insert_index_++;
	}
	void LayerStack::push_overlay(Layer* overlay)
	{
		layers_.emplace_back(overlay);
	}
	void LayerStack::pop_layer(Layer* layer)
	{
		auto it = std::find(layers_.begin(), layers_.end(), layer);
		if (it != layers_.end()) {
			layers_.erase(it);
			layer_insert_index_--;
		}
	}
	void LayerStack::pop_overlay(Layer* overlay)
	{
		auto it = std::find(layers_.begin(), layers_.end(), overlay);
		if (it != layers_.end()) {
			layers_.erase(it);
		}
	}
}