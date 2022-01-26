#pragma once

#include <utility>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Grout {
	class Transform {
	public:
		Transform() {}
		Transform(glm::vec3 position, glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) 
			: world_position_(position), world_scale_(size), euler_rotation_(rotation) {}
		~Transform() {}
		
		const glm::mat4& get_transform() const;

		const glm::vec3& get_position()	const { return world_position_; }
		const glm::vec3& get_rotation()	const { return euler_rotation_; }

		void add_position(const glm::vec3& position) { world_position_ += position; has_changed_ = true; }
		void add_rotation(const glm::vec3& rotation) { euler_rotation_ += rotation; has_changed_ = true; }

		void set_position(const glm::vec3& position) { world_position_ = position; has_changed_ = true; }
		void set_rotation(const glm::vec3& rotation) { euler_rotation_ = rotation; has_changed_ = true; }


		glm::quat get_orientation() const;
		glm::vec3 get_up_direction() const;
		glm::vec3 get_right_direction() const;
		glm::vec3 get_forward_direction() const;

		bool has_changed() const { return has_changed_; }

	private:


	private:
		// Returns true if the transform has changed since last frame
		bool has_changed_ = false;

		// World data
		glm::vec3 world_position_ = glm::vec3(0.0f);
		glm::vec3 euler_rotation_ = glm::vec3(0.0f);
		glm::quat quat_orientation_ = glm::quat();
		// TODO: this one can be tricky (see lossy scale in unity)
		glm::vec3 world_scale_ = glm::vec3(1.0f);
		
		// Axis
		glm::vec3 forward_ = glm::vec3(0.0f);
		glm::vec3 right_ = glm::vec3(0.0f);
		glm::vec3 up_ = glm::vec3(0.0f);

		// Transformation matrix
		glm::mat4 local_to_world_matrix_ = glm::mat4(0.0f);
		glm::mat4 world_to_local_matrix_ = glm::mat4(0.0f);

		// Data related to parent
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
		// Object object_;

	};
}