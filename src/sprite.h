#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "main.h"
#include "gl_program.h"

namespace collapsed {
  class SpriteAsset {
    public:
      SpriteAsset();

    private:
      GLuint vbo, vao;
      GLProgram *program;
      //Texture *texture;
      float boundx, boundy;
  };

  class Sprite {
    public:
      Sprite();
      void set_pos(float x, float y);
      void offset_pos(float x, float y);
    private:
      glm::vec2 pos;
  };
}

#endif
