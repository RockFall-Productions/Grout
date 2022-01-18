#include "grtpch.h"
#include "Camera.h"


#include "Grout/Core/Core.h"

// TODO: maybe remove?
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>

namespace Grout {
	Camera::Camera(const glm::vec3& position, float width, float height)
		: position_(position), width_(width), height_(height), aspect_((float)width/(float)height)
	{
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
			projection_matrix_ = glm::perspective(	glm::radians(field_of_view_), 
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
			glm::quat orientation = get_orientation();

			view_matrix_ = glm::translate(glm::mat4(1.0f), position_) * glm::toMat4(orientation);
			view_matrix_ = glm::inverse(view_matrix_);

			//glm::vec3 camera_front = position_ + forward_vector_;
			//view_matrix_ = glm::lookAt(position_, camera_front, up_vector_);
			
		}
		// ----- ORTHOGRAPHIC -----
		else if (projection_type_ == CameraProjectionType::Orthographic) {
			glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position_) * 
									glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.z), glm::vec3(0, 0, 1));
			view_matrix_ = glm::inverse(transform);
		}

		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	glm::quat Camera::get_orientation() const
	{
		return glm::quat(glm::vec3(-rotation_.y, -rotation_.x, -rotation_.z));
	}

	glm::vec3 Camera::get_up_direction() const
	{
		return glm::rotate(get_orientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::get_right_direction() const
	{
		return glm::rotate(get_orientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::get_forward_direction() const
	{
		return glm::rotate(get_orientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	void Camera::UpdateViewProjectionMatrix()
	{
		UpdateProjectionMatrixOnly();
		UpdateViewMatrixOnly();
	}

	



}