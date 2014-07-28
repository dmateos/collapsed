#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "main.h"
#include "gl_program.h"

namespace collapsed {
  class SpriteAsset {
    private:
    GLuint vbo, vao;
    GLProgram *program;
  };

  class Sprite {
    private:
      glm::vec2 pos;
  };
}

#endif
