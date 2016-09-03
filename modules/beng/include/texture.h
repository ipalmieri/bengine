#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "edefs.h"

namespace engine {
class texture
{
  friend class renderer;

 public:

  inline GLuint object()
  {
    return _object;
  }

 protected:

  texture(const tools::imageMap& pmap);
  ~texture();

  GLuint _object;

  static GLenum texFormat(const tools::imageMap& pmap)
  {
    //fix this - use enum not integers
    switch (pmap.channels()) {
      case 1:
        return GL_LUMINANCE;
      case 3:
        return GL_RGB;
      default:
        throw std::runtime_error("Invalid imageMap to texture format");
    }
  }

  static texture* loadTextureFromFile(const std::string& filename);

};



}

#endif
