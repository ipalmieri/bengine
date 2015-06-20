#ifndef __MESH_H__
#define __MESH_H__

#include "edefs.h"


#define TAM_VERTEX 4
#define TAM_NORMAL 3
#define TAM_TEXTUR 2

namespace engine
{

   struct mvertex
   {
      float vertex[TAM_VERTEX];
      float normal[TAM_NORMAL];
      float texcoord[TAM_TEXTUR];
   };


   struct mtriangle
   {
      unsigned v0;
      unsigned v1;
      unsigned v2;
   };


   class mesh
   {
      friend class renderer;

     public:
      
      void draw() const;

      inline unsigned vertexCount() const { return _vcount; } 
      inline unsigned indexCount() const { return _icount; }

      void setVertexBuffer(mvertex *buff, const unsigned &count) ;
      void setIndexBuffer(mtriangle *buff, const unsigned &count);

     protected:

      mesh();
      ~mesh();
      
      GLuint _ibuffer;
      GLuint _vbuffer;
      GLuint _varray;

      unsigned _vcount;
      unsigned _icount;

   };

   //sample cube mesh
   void createCubeMesh(mesh *ms, const float &size);
   void createPlaneMesh(mesh *ms, const unsigned &width, const unsigned &length, const float &unit = 1.0f);
   void createSphereMesh(mesh *ms, const float &radius, const unsigned &rings, const unsigned &sectors);

}

#endif
