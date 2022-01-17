#include "grtpch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Grout {
	Camera::Camera(const glm::vec3& position, float width, float height)
		: position_(position), width_(width), height_(height), aspect_(width/height)
	{
		near_clip_plane_ = -1.0f;
		UpdateViewProjectionMatrix();
	}

	/*Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, float width, float height)
		: position_(position), rotation_(rotation), width_(width), height_(height), aspect_(width / height)
	{
		UpdateViewProjectionMatrix();
	}*/



	void Camera::UpdateProjectionMatrixOnly()
	{
		if (projection_type_ == CameraProjectionType::Perspective) {
			projection_matrix_ = glm::perspective(	glm::radians<float>(field_of_view_), 
													(float)aspect_, 
													near_clip_plane_, 
													far_clip_plane_
												 );
			
		}

		else if (projection_type_ == CameraProjectionType::Orthographic) {
			projection_matrix_ = glm::ortho(position_.x - (width_ / 2.0f),
											position_.x + (width_ / 2.0f),
											position_.y - (height_ / 2.0f),
											position_.y + (height_ / 2.0f), 
											near_clip_plane_,
											far_clip_plane_
											);
		}

		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void Camera::UpdateViewMatrixOnly()
	{
		// ------ PERSPECTIVE ------
		if (projection_type_ == CameraProjectionType::Perspective) {
			UpdateCameraVectors();
			glm::vec3 camera_front = position_ + foward_vector_;
			view_matrix_ = glm::lookAt(position_, camera_front, up_vector_);
			
		}
		// ----- ORTHOGRAPHIC -----
		else if (projection_type_ == CameraProjectionType::Orthographic) {
			glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position_) * 
									glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.z), glm::vec3(0, 0, 1));
			view_matrix_ = glm::inverse(transform);
		}

		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void Camera::UpdateViewProjectionMatrix()
	{
		UpdateProjectionMatrixOnly();
		UpdateViewMatrixOnly();
	}

	void Camera::UpdateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 foward;
		foward.x = cos(glm::radians(rotation_.y)) * cos(glm::radians(rotation_.x));
		foward.y = sin(glm::radians(rotation_.y));
		foward.z = cos(glm::radians(rotation_.y)) * sin(glm::radians(rotation_.x));
		foward_vector_ = glm::normalize(foward);
		//foward_vector_ = glm::vec3(0.0f, 0.0f, 1.0f);
		// The Right vector from the Front
		right_vector_ = glm::normalize(glm::cross(foward_vector_, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		// The Up vector from Right and Front
		up_vector_ = glm::normalize(glm::cross(right_vector_, foward_vector_));
	}

}