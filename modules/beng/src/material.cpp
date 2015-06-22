#include "material.h"
#include "program.h"
#include "texture.h"

using namespace std;
using namespace engine;
using namespace tools;

material::material()
{
   diffuseColor = DEF_COLOR;
   specularColor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

   shininess = 10.0f;
   
   diffuseMap = (texture *) NULL;
   
}

material::~material()
{

}


void material::apply(program *prog)
{

   prog->setUniform(DIFF_MATERIAL_UNIF, diffuseColor);
   
   prog->setUniform(SPEC_MATERIAL_UNIF, specularColor);
   
   prog->setUniform(SHIN_MATERIAL_UNIF, shininess);

   //diffuseMap
   if (diffuseMap)
   {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap->object());
      prog->setUniform(DIFF_MAP_UNIF, 0);
   }



}


void material::remove()
{
   //diffuseMap
   if (diffuseMap)
   {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, 0);
   }

}
