#pragma once

#include <utility>
#include <string>
//#include <cstdint>
//#include <ctime>

namespace Grout {
	// Represent some amount of time in seconds
	class Timestep {
	public:
		Timestep(float time = 0.0f) : time_(time) { }

		double get_seconds()		 const { return time_; }
		double get_milliseconds() const { return time_ * 1000.0f; }

		// --------- Types ---------
		operator float() const {
			return float(time_);
		}
		operator double() const {
			return double(time_);
		}
		operator std::string() const {
			return std::to_string(time_);
		}
		// --------- Subtraction ---------
		friend Timestep operator-(Timestep const &lhs, Timestep const &rhs) {
			return Timestep(lhs.time_ - rhs.time_);
		}
		friend Timestep operator-(double const& lhs, Timestep const& rhs) {
			return Timestep(lhs - double(rhs.time_));
		}
		friend Timestep operator-(Timestep const& lhs, double const& rhs) {
			return Timestep(double(lhs.time_) - rhs);
		}
		// --------- Equal ---------
		Timestep& operator=(const double& num) {
			time_ = double(num);
			return *this;
		}
		Timestep& operator=(const float& num) {
			time_ = double(num);
			return *this;
		}
		Timestep& operator=(const int& num) {
			time_ = double(num);
			return *this;
		}

	private:
		double time_;
	};

	// Holds all time related information in this ambient
	class Time {
	public:
		// Return the deltatime as float
		static float	delta_time_f()	{ return float(delta_time_); }
		// Returns the deltatime as double
		static double	delta_time_d()	{ return double(delta_time_); }
		static Timestep delta_time() { return delta_time_; }

		// Returns the deltatime as double
		static uint32_t	get_frame_count() { return frame_count_; }

		static void OnUpdate();

	private:
		Time() {}

		// Time at the beggining of current frame
		static Timestep time_;
		// Interval in seconds from last frame to current one
		static Timestep delta_time_;

		// Total number of frames since the start of application
		static uint32_t frame_count_;
	};
}