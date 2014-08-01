#include "texture.h"

using namespace collapsed;

Texture::Texture() {
  glGenTextures(1, &m_tex);
  glBindTexture(GL_TEXTURE_2D, m_tex);

  /* How do we handle up/down scale. */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* What kind of filter. */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  float pixels[] = {
      0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
  };

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind_texture() const {
  glBindTexture(GL_TEXTURE_2D, m_tex);
}
