#include "grtpch.h"
#include "Transform.h"


namespace Grout {
    const glm::mat4 Transform::get_transform() const
    {
        glm::mat4 transform = glm::mat4(1.0f);

        transform = glm::translate(transform, world_position_);
        transform = glm::rotate(transform, euler_rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, euler_rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, euler_rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, world_scale_);

        return transform;
    }
    glm::quat Grout::Transform::get_orientation() const
    {
        return glm::quat(glm::vec3(-euler_rotation_.y, -euler_rotation_.x, -euler_rotation_.z));
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
