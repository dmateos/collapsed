#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "main.h"
#include "gl_program.h"

namespace collapsed {
  class SpriteAsset {
    public:
      SpriteAsset(GLProgram *program);
      GLuint m_vbo, m_vao;
      GLProgram *m_program;
      float m_mesh[8];
      //Texture *texture;
  };

  class Sprite {
    public:
      Sprite(SpriteAsset *asset);
      void set_pos(float x, float y);
      void offset_pos(float x, float y);

      SpriteAsset *m_asset;
    private:
      glm::vec2 pos;
  };
}

#endif
