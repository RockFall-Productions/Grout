#include "grtpch.h"
#include "Camera.h"


#include "Grout/Core/Core.h"

// TODO: maybe remove?
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>

namespace Grout {
	Camera::Camera(const glm::vec3& position, float width, float height)
		: transform_(Transform(position)), width_(width), height_(height), aspect_((float)width/(float)height)
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
			projection_matrix_ = glm::ortho(transform_.get_position().x - (width_ / 2.0f),
											transform_.get_position().x + (width_ / 2.0f),
											transform_.get_position().y - (height_ / 2.0f),
											transform_.get_position().y + (height_ / 2.0f),
											near_clip_plane_,
											far_clip_plane_
											);
		}
	}

	void Camera::UpdateViewMatrixOnly()
	{
		// ------ PERSPECTIVE ------
		if (projection_type_ == CameraProjectionType::Perspective) {
			glm::quat orientation = transform_.get_orientation();

			view_matrix_ = glm::translate(glm::mat4(1.0f), transform_.get_position()) * glm::toMat4(orientation);
			view_matrix_ = glm::inverse(view_matrix_);

			//glm::vec3 camera_front = position_ + forward_vector_;
			//view_matrix_ = glm::lookAt(position_, camera_front, up_vector_);
			
		}
		// ----- ORTHOGRAPHIC -----
		else if (projection_type_ == CameraProjectionType::Orthographic) {
			glm::mat4 transform =	glm::translate(glm::mat4(1.0f), transform_.get_position()) * 
									glm::rotate(glm::mat4(1.0f), glm::radians(transform_.get_rotation().z), glm::vec3(0, 0, 1));
			view_matrix_ = glm::inverse(transform);
		}
	}

	const glm::mat4& Camera::get_viewprojection_matrix()
	{
		if (transform_.has_changed()) {
			UpdateViewProjectionMatrix();
		}

		return view_projection_matrix_;
	}

	const glm::mat4& Camera::get_projection_matrix()
	{
		if (transform_.has_changed()) {
			UpdateViewProjectionMatrix();
		}

		return projection_matrix_;
	}

	const glm::mat4& Camera::get_view_matrix()
	{
		if (transform_.has_changed()) {
			UpdateViewProjectionMatrix();
		}

		return view_matrix_;
	}

	void Camera::UpdateViewProjectionMatrix()
	{
		UpdateProjectionMatrixOnly();
		UpdateViewMatrixOnly();

		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	



}