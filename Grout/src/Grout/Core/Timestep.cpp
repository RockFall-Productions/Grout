#include "grtpch.h"
#include "Timestep.h"

#include <glfw/glfw3.h>

namespace Grout {
	Timestep Time::time_ = Timestep();
	Timestep Time::delta_time_ = Timestep();
	uint32_t Time::frame_count_ = 0;

	void Time::OnUpdate()
	{
		double curr_time = glfwGetTime();
		delta_time_ = curr_time - time_;
		time_ = curr_time;

		++frame_count_;
	}
}
