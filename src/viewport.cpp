#include "viewport.h"

using namespace engine;

viewport::viewport(const int &x, const int &y, const unsigned &width, const unsigned &height)
{
   _x = x;
   _y = y;

   _width = width;
   _height = height;
}

viewport::~viewport()
{

}

void viewport::reset(const int &x, const int &y, const unsigned &width, const unsigned &height)
{
   _x = x;
   _y = y;

   _width = width;
   _height = height;

   apply();
}


void viewport::apply()
{
   glViewport((GLint)_x, (GLint)_y, (GLsizei)_width, (GLsizei)_height);
}
