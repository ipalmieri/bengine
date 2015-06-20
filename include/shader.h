#ifndef __SHADER_H__
#define __SHADER_H__

#include "edefs.h"
#include <string>


namespace engine
{
   class shader
   {
      friend class renderer;

     public:
      
      inline GLuint object() const { return _object; }

     protected:

      shader(const std::string &code, const GLenum &type);
      ~shader();

      static shader *shaderFromFile(const std::string &filename, const GLenum &type);

      GLuint _object;


   };
}

#endif
