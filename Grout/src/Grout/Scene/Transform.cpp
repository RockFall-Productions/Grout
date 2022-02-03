#include "grtpch.h"
#include "Transform.h"


namespace Grout {
    const glm::mat4 Transform::get_transform_matrix() const
    {
        glm::mat4 transform = glm::mat4(1.0f);

        // Translate
        transform = glm::translate(transform, world_position_);
        // Rotate
        glm::mat4 rotation_matrix = glm::toMat4(get_orientation());
        transform = transform * rotation_matrix;
        // Scale
        transform = glm::scale(transform, world_scale_);

        return transform;
    }

    void Transform::set_yaw_pitch_roll(const glm::vec3& yaw_pitch_roll)
    {
        yaw_pitch_roll_ = yaw_pitch_roll;
        if (yaw_pitch_roll_.z != 0.0f) {
            GRT_ERROR("Trying to change Transform's roll: Roll is not yet supported");
        }
        // Quaternion = (-pitch, -yaw, roll??)
        quat_orientation_ = glm::quat(glm::vec3(-yaw_pitch_roll_.x, -yaw_pitch_roll_.y, yaw_pitch_roll_.z));
        has_changed_ = true;
    }

    void Transform::add_yaw(const float yaw)
    {
        yaw_pitch_roll_.x += yaw;
        if (yaw_pitch_roll_.z != 0.0f) {
            GRT_ERROR("Trying to change Transform's roll: Roll is not yet supported");
        }
        // Quaternion = (-pitch, -yaw, roll??)
        quat_orientation_ = glm::quat(glm::vec3(-yaw_pitch_roll_.y, -yaw_pitch_roll_.x, yaw_pitch_roll_.z));
        has_changed_ = true;
    }

    void Transform::add_pitch(const float pitch)
    {
        yaw_pitch_roll_.y += pitch;
        if (yaw_pitch_roll_.z != 0.0f) {
            GRT_ERROR("Trying to change Transform's roll: Roll is not yet supported");
        }
        // Quaternion = (-pitch, -yaw, roll??)
        quat_orientation_ = glm::quat(glm::vec3(-yaw_pitch_roll_.y, -yaw_pitch_roll_.x, yaw_pitch_roll_.z));
        has_changed_ = true;
    }

    void Transform::look_at(const glm::vec3& target)
    {
        yaw_pitch_roll_ = glm::vec3(0.0f);

        glm::vec3 direction = target - world_position_;
        direction = glm::normalize(direction);

        quat_orientation_ = glm::quatLookAt(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::quat Grout::Transform::get_orientation() const
    {
        //return glm::quat(glm::vec3(-euler_rotation_.y, -euler_rotation_.x, -euler_rotation_.z));
        return quat_orientation_;
    }

    glm::vec3 Grout::Transform::get_up_direction() const
    {
        return glm::rotate(get_orientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 Grout::Transform::get_right_direction() const
    {
        return glm::rotate(get_orientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::vec3 Grout::Transform::get_forward_direction() const
    {
        return glm::rotate(get_orientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }
}
