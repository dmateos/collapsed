#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

namespace collapsed {
  class Camera {
    public:
      Camera();
      void set_position(const glm::vec2 &position);
      void offset_position(const glm::vec2 &position);
      glm::mat4 matrix(); 
    private:
      glm::vec2 m_position;
  };
}

#endif
