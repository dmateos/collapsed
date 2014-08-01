#include "sprite.h"

using namespace collapsed;

SpriteAsset::SpriteAsset(GLProgram *program, Texture *texture) :
  m_program(program),
  m_texture(texture)
{
  float verticies[] = {
    -1.0f, +1.0f, 0.0f, 0.0f,
    +1.0f, +1.0f, 1.0f, 0.0f,
    +1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f
  };

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0 
  };

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  /* Setup a buffer for our verticies. */
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  /* One for our vertecies indexes */
  glGenBuffers(1, &m_veo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  glEnableVertexAttribArray(m_program->get_attrib("vp"));
  glVertexAttribPointer(m_program->get_attrib("vp"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), NULL);

  glEnableVertexAttribArray(m_program->get_attrib("texcoord"));
  glVertexAttribPointer(m_program->get_attrib("texcoord"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 
      (void*)(2*sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Sprite::Sprite(SpriteAsset *asset) :
  m_pos(0.0, 0.0),
  m_asset(asset)
{

}

void Sprite::set_pos(float x, float y) {
  m_pos.x = x;
  m_pos.y = y;
}

glm::vec2 Sprite::get_pos() const {
  return m_pos;
}

void Sprite::offset_pos(float x, float y) {
  m_pos.x += x;
  m_pos.y += y;
}
