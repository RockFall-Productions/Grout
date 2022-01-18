#include "grtpch.h"
#include "Transform.h"


namespace Grout {
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
