#include "sprite.h"

using namespace collapsed;

SpriteAsset::SpriteAsset(GLProgram *program) :
  m_program(program)
{
  float square[8] = {
    -1.0f, -1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f,
    1.0f, -1.0f
  };
 // memcpy(mesh, square, sizeof(float)*8);

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), square, GL_STATIC_DRAW);

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray(m_program->get_attrib("vp"));
  glVertexAttribPointer(m_program->get_attrib("vp"), 2, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Sprite::Sprite(SpriteAsset *asset) :
  pos(0.0, 0.0),
  m_asset(asset)
{

}

void Sprite::set_pos(float x, float y) {
  pos.x = x;
  pos.y = y;
}

void Sprite::offset_pos(float x, float y) {
  pos.x += x;
  pos.y += y;
}
