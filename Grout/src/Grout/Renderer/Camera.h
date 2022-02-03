#pragma once

#include <glm/glm.hpp>
#include "Grout/Events/Event.h"
#include "Grout/Events/MouseEvent.h"
#include "Grout/Core/Time.h"
#include "Grout/Scene/Transform.h"

namespace Grout {
	class Camera
	{
	public:
		// TODO: Builder constructor
		Camera(const glm::vec3& position = (glm::vec3(0)), float width = 600.0f, float height = 400.0f);
		//Camera(const glm::vec3& position = (glm::vec3(0)), const glm::vec3& rotation = (glm::vec3(0)), float width = 600.0f, float height = 400.0f);
	public:
		//////////////////////////////////////// SETTERS AND GETTERS ////////////////////////////////////////
		const glm::vec3& get_speed()	const { return speed_; }
		void add_speed(const glm::vec3& speed)	{ speed_ += speed; }
		void add_speed(const float& speed)		{ speed_ += speed; }
		void set_speed(const glm::vec3& speed)	{ speed_ = speed; }
		void set_speed(const float& speed)		{ speed_ = glm::vec3(speed); }

		const glm::vec3& get_target()	const { return target_; }
		void set_target(const glm::vec3& target) { target_ = target; }

		Transform& get_transform() { return transform_;  }

		const glm::mat4& get_viewprojection_matrix();
		const glm::mat4& get_projection_matrix();
		const glm::mat4& get_view_matrix();

		static const Ref<Camera>& get_main() { return main_; }
		static void set_main(const Ref<Camera>& main) { main_ = main; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
		void LookAtTarget() { transform_.look_at(target_); }

		void LerpLookAtTarget(const glm::vec3& target, float factor) {
			factor *= Time::delta_time_f();
			glm::vec3 lerp_target = factor * transform_.get_position() + (1 - factor) * target;
			transform_.set_position(lerp_target);
		}

		void LerpMoveToTarget(const glm::vec3& target, float factor) { 
			//glm::vec3 lerp_target = factor * transform_.get_position() + (1 - factor) * target;
			glm::vec3 lerp_target = target - transform_.get_position();
			lerp_target = glm::normalize(lerp_target) * factor * Time::delta_time_f();
			transform_.add_position(lerp_target);
		}

	private:
		// Updates both the View and Projection Matrix
		void UpdateViewProjectionMatrix();
		// Updates the PROJECTION Matrix (and the ViewProjection)
		void UpdateProjectionMatrixOnly();
		// Updates the VIEW Matrix (and the ViewProjection)
		void UpdateViewMatrixOnly();
	
	private:
		//  ENUMS
		enum class CameraClearType {
			Skybox,
			SolidColor
		};
		enum class CameraProjectionType {
			Perspective,
			Orthographic
		};
	private:
		//  STATIC PROPERTIES
		static std::vector<Camera> all_cameras_;
		static uint32_t all_cameras_count_;
		static Camera* current;
		static Ref<Camera> main_;
	private:
		//  PROPERTIES
		
		// -- World Space variables --
		Transform transform_;
		glm::vec3 target_;
		// Rotation in X, Y and Z axis (euler degrees °)
		glm::vec3 speed_ = glm::vec3(0.0f);

		// Viewport
		float width_;
		float height_;

		// The point in which the camera is looking at
		// TODO: Add target tracking system
		//glm::vec3 focal_point_;

		// Angle of visibility from center (for PERSPECTIVE projection ONLY)
		float field_of_view_ = 45.0f;
		// Width / Height
		float aspect_;

		// Distance from camera to NEAR clip plane
		float near_clip_plane_ = 1.0f;
		// Distance from camera to FAR clip plane
		float far_clip_plane_ = 500.0f;

		// Transformation matrixes
		glm::mat4 camera_to_world_matrix = glm::mat4(0);
		glm::mat4 world_to_camera_matrix = glm::mat4(0);
		
		// Switch between orthographic to perspective
		CameraProjectionType projection_type_ = CameraProjectionType::Perspective;

		// Transforms the view space into clip space
		glm::mat4 projection_matrix_ = glm::mat4(0);
		// Inversion of the transformation matrix of the camera
		glm::mat4 view_matrix_ = glm::mat4(0);
		// Used isntead of doing the multiplication multiple times
		glm::mat4 view_projection_matrix_ = glm::mat4(0);

		// Tells how the camera should clear the background
		// -> Skybox or SolidColor
		CameraClearType clear_type_ = CameraClearType::SolidColor;
		glm::vec4 background_color_ = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		
		// TODO: Scenes
		// Scene scene
	};
}

