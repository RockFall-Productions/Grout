#pragma once

#include <string>

namespace Grout {
	class Object {
	public:

	private:
		bool active_in_hierarchy_;
		bool active_;

		std::string name;
		std::string tag;

		Transform transform;

		// Layer layer_;
		// Scene scene_;



	};
}