#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "edefs.h"

//shader attribute locations
#define LOC_VERTEX 0
#define LOC_NORMAL 1
#define LOC_TEXTUR 2

#define ATT_VERTEX "vVertex"
#define ATT_NORMAL "vNormal"
#define ATT_TEXCOR "vTexCoord"
//---

//shader uniform names
#define MODEL_UNIF "model"
#define VIEW_UNIF "view"
#define PROJ_UNIF "projection"

#define DIFF_MATERIAL_UNIF "material.diffuseColor"
#define SPEC_MATERIAL_UNIF "material.specularColor"
#define SHIN_MATERIAL_UNIF "material.shininess"
#define DIFF_MAP_UNIF "material.diffuseMap"

#define POSITION_LIGHT_UNIF "light.position"
#define COLOR_LIGHT_UNIF "light.color"
#define KC_LIGHT_UNIF "light.kc"
#define KL_LIGHT_UNIF "light.kl"
#define KQ_LIGHT_UNIF "light.kq"
#define AMB_LIGHT_UNIF "light.ambientCoef"

#define GAMMA_UNIF "gamma"
//---

namespace engine
{
   class shader;

   class program
   {
      
      friend class renderer;

     public:
      
      inline GLuint object() const { return _object; }
      void apply() const;
      bool isApplied() const;
      void remove() const;
      
      GLint attrib(const GLchar* name) const;
      GLint uniform(const GLchar* name) const;


      void setUniform(const GLchar *name, const int &value);
      void setUniform(const GLchar *name, const Real &value);
      void setUniform(const GLchar *name, const tools::Vector3 &v);
      void setUniform(const GLchar *name, const tools::Vector4 &v);
      void setUniform(const GLchar *name, const tools::transMatrix  &m, 
		      GLboolean transpose = GL_TRUE);


     protected:

      program(const std::vector<shader *> &shaders);
      ~program();
    
      GLuint _object;
        
      //copying disabled
      program(const program&);
      const program& operator=(const program&);  

   };
}

#endif
