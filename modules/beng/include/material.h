#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "algebra.h"
#include "edefs.h"

namespace engine
{
   class program;
   class texture;

   class material
   {
      friend class renderer;
   
     public:

      void apply(program *prog);
      void remove();

      tools::Vector4 diffuseColor;
      tools::Vector4 specularColor;

      Real shininess;

      texture *diffuseMap;

     protected:

      material();
      ~material();

   };
}

#endif
