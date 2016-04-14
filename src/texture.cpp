#include "texture.h"

using namespace std;
using namespace tools;
using namespace engine;

texture::texture(const imageMap &pmap)
{
   glGenTextures(1, &_object);

   glBindTexture(GL_TEXTURE_2D, _object);

   
   //fix this - maybe use mipmap
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    
   /*
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
     (GLsizei) pmap.width(), (GLsizei) pmap.height(),
     0, texFormat(pmap), GL_UNSIGNED_BYTE, pmap.data());
   */

   
   glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 
		  pmap.width(), pmap.height());


   glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pmap.width(), pmap.height(),
		   texFormat(pmap), GL_UNSIGNED_BYTE, pmap.data());


   glBindTexture(GL_TEXTURE_2D, 0);

}

texture::~texture()
{
   glDeleteTextures(1, &_object);
}

texture *texture::loadTextureFromFile(const string &filename)
{
   texture *ret = (texture *) NULL;
   imageMap pmap;

   string filepath = TEXTURE_PATH + filename;

   readJPEG((char *) filepath.c_str(), pmap);
   
   if (pmap.data())
   {
      pmap.flipVertical();

      ret = new texture(pmap);
   }

   return ret;
}
