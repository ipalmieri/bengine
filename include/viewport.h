#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "edefs.h"

namespace engine
{
   class viewport
   {
     public:
      viewport(const int &x, const int &y, const unsigned &width, const unsigned &height);
      ~viewport();

      void reset(const int &x, const int &y, const unsigned &width, const unsigned &height);

      void apply();

     protected:

      //position of the lower left corner
      int _x;
      int _y;


      unsigned _width;
      unsigned _height;


   };
}

#endif
