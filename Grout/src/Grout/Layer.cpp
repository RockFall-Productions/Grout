#include "grtpch.h"
#include "Layer.h"

namespace Grout {
	Layer::Layer(const std::string& name, bool enabled)
		: debug_name_(name), enabled_(enabled)
	{
	}
	Layer::~Layer()
	{
	}
}