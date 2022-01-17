#pragma once

#include <glm/glm.hpp>

namespace Grout {
	class Camera
	{
	public:
		Camera(const glm::vec3& position = (glm::vec3(0)), float width = 600.0f, float height = 400.0f);
		//Camera(const glm::vec3& position = (glm::vec3(0)), const glm::vec3& rotation = (glm::vec3(0)), float width = 600.0f, float height = 400.0f);
	public:
		// ----- SETTERS AND GETTERS -----/
		void			 set_position(const glm::vec3& position) { position_ = position; UpdateViewMatrixOnly();  }
		const glm::vec3& get_position() const { return position_; }

		void			 set_rotation(const glm::vec3& rotation) { rotation_ = rotation; UpdateViewMatrixOnly();  }
		const glm::vec3& get_rotation() const { return rotation_; }

		const glm::mat4& get_projection_matrix()	 const { return projection_matrix_;  }
		const glm::mat4& get_view_matrix()			 const { return view_matrix_;  }
		const glm::mat4& get_viewprojection_matrix() const { return view_projection_matrix_;  }
	private:
		// 
		void UpdateProjectionMatrixOnly();
		void UpdateViewMatrixOnly();
		void UpdateViewProjectionMatrix();
		void UpdateCameraVectors();
	
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
		float width_;
		float height_;
		// TODO: Quaternions
		// Rotation in X, Y and Z in euler degrees
		glm::vec3 rotation_		= glm::vec3(0.0f);
		glm::vec3 foward_vector_ = glm::vec3(0.0f);
		glm::vec3 right_vector_ = glm::vec3(0.0f);
		glm::vec3 up_vector_	= glm::vec3(0.0f);
		// The point in which the camera is looking at
		// TODO: Add target tracking system
		//glm::vec3 target_;

		// In degrees
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
		CameraProjectionType projection_type_ = CameraProjectionType::Orthographic;

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

