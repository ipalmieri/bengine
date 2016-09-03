#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "algebra.h"
#include "program.h"
#include "edefs.h"

namespace engine {
class light
{
  friend class renderer;

 public:

  void apply(program* prog);
  void remove();

  Real kc; //constant attenuation
  Real kl; //linear
  Real kq; //quadratic

  tools::vector4 position;
  tools::vector4 color;

  Real ambientCoef;


 protected:

  light(const tools::vector4& pos); //w = 0 -> directional light source
  ~light();


};
}

#endif
