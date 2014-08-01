#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

namespace collapsed {
  class Texture {
    public:
      Texture();
      void bind_texture() const;
    private:
      GLuint m_tex;
  };
}

#endif
