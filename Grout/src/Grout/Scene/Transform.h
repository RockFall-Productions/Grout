#pragma once

#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Grout {
	class Transform {
	public:
		Transform() {}
		Transform(glm::vec3 position, glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) 
			: world_position_(position), world_scale_(size), yaw_pitch_roll_(rotation) {

			quat_orientation_ = glm::quat(yaw_pitch_roll_);
		}
		~Transform() {}
		
		// Model matrix (translate, rotate and scale)
		const glm::mat4 get_transform_matrix() const;

		// Position
		const glm::vec3& get_position()	const { return world_position_; }
		void add_position(const glm::vec3& position) { world_position_ += position; has_changed_ = true; }
		void set_position(const glm::vec3& position) { world_position_ = position; has_changed_ = true; }

		// Rotation
		const glm::vec3& get_yaw_pitch_roll()	const { return yaw_pitch_roll_; }
		void set_yaw_pitch_roll(const glm::vec3& yaw_pitch_roll);
		// TODO: Roll not yet supported
		void add_yaw(const float yaw);
		void add_pitch(const float pitch);

		//void add_rotation(const glm::vec3& rotation) { yaw_pitch_roll_ += rotation; has_changed_ = true; }

		// Scale
		void set_scale(const glm::vec3& scale) { world_scale_ = scale; has_changed_ = true; }

		// Turns the orientation to a given target position
		void look_at(const glm::vec3& target);

		// Get directions (all Quaternion based)
		glm::quat get_orientation() const;
		glm::vec3 get_up_direction() const;
		glm::vec3 get_right_direction() const;
		glm::vec3 get_forward_direction() const;

		// True if position, scale or rotation has changed since last frame
		bool has_changed() const { return has_changed_; }
	private:


	private:
		// Returns true if the transform has changed since last frame
		bool has_changed_ = false;

		// World data
		glm::vec3 world_position_ = glm::vec3(0.0f);
		glm::vec3 yaw_pitch_roll_ = glm::vec3(0.0f);
		// TODO: this one can be tricky (see lossy scale in unity)
		glm::vec3 world_scale_ = glm::vec3(1.0f);
		// Quaternion main orientation
		glm::quat quat_orientation_ = glm::quat();

		// Transformations matrices
		glm::mat4 local_to_world_matrix_ = glm::mat4(0.0f);
		glm::mat4 world_to_local_matrix_ = glm::mat4(0.0f);


		//		Data related to parent		 //
												/*
		glm::vec3 local_position_;
		glm::vec3 local_euler_rotation_;
		glm::vec3 local_quat_rotation_;
		glm::vec3 local_scale_;
		

		Transform* parent;
		// Return the top parent in hierarchy
		Transform* root;
		uint32_t child_count_;
												*/
	};
}