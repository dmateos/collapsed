#include "sprite.h"

using namespace collapsed;

SpriteAsset::SpriteAsset(GLProgram *program, Texture *texture, int tpx, int tpy) :
  m_program(program),
  m_texture(texture)
{
  float width = 914.0f;
  float height = 936.0f;

  float tw = 70.0f;
  float th = 70.0f;

  float xl = (tw * tpx) / width;
  float yl = (th * tpy) / height;
  float xr = (tw * tpx) / width + (tw/width);
  float yr = (th * tpy) / height + (th/height);

  float verticies[] = {
    -5.0f, +5.0f, xl, yl, //top left
    +5.0f, +5.0f, xr, yl,  //top right
    +5.0f, -5.0f, xr, yr, //bottom right
    -5.0f, -5.0f, xl, yr //bottom left
  };

  memcpy(&m_verticies, verticies, sizeof(verticies));

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0 
  };

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  /* Setup a buffer for our verticies. */
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_verticies), m_verticies, GL_STATIC_DRAW);

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
  m_position(0.0, 0.0),
  m_asset(asset)
{

}

void Sprite::set_position(float x, float y) {
  m_position.x = x;
  m_position.y = y;
}

glm::vec2 Sprite::get_position() const {
  return m_position;
}

void Sprite::offset_position(float x, float y) {
  m_position.x += x;
  m_position.y += y;
}

void Sprite::animation_step(float step) {
}
