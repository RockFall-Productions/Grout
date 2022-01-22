#include "grtpch.h"
#include "Object.h"

namespace Grout {
	Grout::Object::Object(std::string name, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation)
		: name_(name)
	{
		transform = Transform(pos, size, rotation);
	}
}
