#include "camera.h"

using namespace collapsed;

Camera::Camera() :
  m_position(0, 0)
{

}

void Camera::set_position(const glm::vec2 &position) {
  m_position = position;
}

glm::vec2 Camera::get_position() {
  return m_position;
}

void Camera::offset_position(const glm::vec2 &position) {
  m_position += position;
}

glm::mat4 Camera::matrix() {
    return glm::ortho(-10.0f, 10.0f*ZOOM, -10.0f*ZOOM, 10.0f) * 
      glm::translate(glm::mat4(), glm::vec3(m_position, 0.0));
   // return glm::ortho(0, (float)XRES, (float)YRES, 0);
}
