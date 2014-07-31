#include "camera.h"

using namespace collapsed;

Camera::Camera() :
  m_position(0, 0)
{

}

void Camera::set_position(glm::vec2 &position) {

}

void Camera::offset_position(glm::vec2 &position) {

}

glm::mat4 Camera::matrix() {
    return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,-0.1f, 1.0f);
}
