#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "main.h"

namespace collapsed {
  class SpriteAsset {
    private:
    GLuint vbo, vao;
  };

  class Sprite {
    private:
      glm::vec2 pos;
  };
}

#endif
