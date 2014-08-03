#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "main.h"
#include "gl_program.h"
#include "texture.h"

namespace collapsed {
  class SpriteAsset {
    public:
      SpriteAsset(GLProgram *program, Texture *texture);

      GLuint m_vbo, m_vao, m_veo;
      GLProgram *m_program;
      Texture *m_texture;
      float m_mesh[8];
  };

  class Sprite {
    public:
      Sprite(SpriteAsset *asset);
      void set_pos(float x, float y);
      glm::vec2 get_pos() const;
      void offset_pos(float x, float y);
      void animation_step(float step);

      SpriteAsset *m_asset;
    private:
      glm::vec2 m_pos;
  };
}

#endif
