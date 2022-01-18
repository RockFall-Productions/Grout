#pragma once

#include <glm/glm.hpp>
#include "Grout/Events/Event.h"
#include "Grout/Events/MouseEvent.h"

namespace Grout {
	class Camera
	{
	public:
		// TODO: Builder constructor
		Camera(const glm::vec3& position = (glm::vec3(0)), float width = 600.0f, float height = 400.0f);
		//Camera(const glm::vec3& position = (glm::vec3(0)), const glm::vec3& rotation = (glm::vec3(0)), float width = 600.0f, float height = 400.0f);
	
	public:
		//////////////////////////////////////// SETTERS AND GETTERS ////////////////////////////////////////
		void add_position (const glm::vec3& position) { position_ += position;		UpdateViewMatrixOnly();  }
		void add_rotation (const glm::vec3& rotation) { rotation_ += rotation;		UpdateViewMatrixOnly();  }
		void add_speed	  (const glm::vec3& speed)	  { speed_ += speed;			UpdateViewMatrixOnly(); }
		void add_speed	  (const float& speed)		  { speed_ += speed;			UpdateViewMatrixOnly(); }

		void set_position (const glm::vec3& position) { position_ = position;		UpdateViewMatrixOnly();  }
		void set_rotation (const glm::vec3& rotation) { rotation_ = rotation;		UpdateViewMatrixOnly();  }
		void set_speed	  (const glm::vec3& speed)	  { speed_ = speed;				UpdateViewMatrixOnly(); }
		void set_speed	  (const float& speed)		  { speed_ = glm::vec3(speed);	UpdateViewMatrixOnly(); }

		const glm::vec3& get_position()	const { return position_; }
		const glm::vec3& get_rotation()	const { return rotation_; }
		const glm::vec3& get_speed()	const { return position_; }

		glm::quat get_orientation() const;
		glm::vec3 get_up_direction() const;
		glm::vec3 get_right_direction() const;
		glm::vec3 get_forward_direction() const;

		const glm::mat4& get_viewprojection_matrix() const { return view_projection_matrix_;  }
		const glm::mat4& get_projection_matrix()	 const { return projection_matrix_;  }
		const glm::mat4& get_view_matrix()			 const { return view_matrix_;  }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		static Camera* main;
	private:
		//  PROPERTIES
		
		// -- World Space variables --
		glm::vec3 position_;
		// Rotation in X, Y and Z axis (euler degrees °)
		glm::vec3 rotation_ = glm::vec3(0.0f);
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
		float near_clip_plane_ = 0.1f;
		// Distance from camera to FAR clip plane
		float far_clip_plane_ = 100.0f;

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


	class OrtographicCamera : public Camera {
	public:

	};

	class PerspectiveCamera : public Camera {
	public:

	};
}

