#include "light.h"

using namespace engine;
using namespace tools;

light::light(const vector4& pos)
{
  //fix this - initial values

  position = pos;

  color = vector4(1.0f, 1.0f, 1.0f, 1.0f);

  //attenuation coefficients
  kc = 1.00f;
  kl = 0.00f;
  kq = 0.00f;

  ambientCoef = 0.1;

}

light::~light()
{

}

void light::apply(program* prog)
{

  prog->setUniform(POSITION_LIGHT_UNIF, position);
  prog->setUniform(COLOR_LIGHT_UNIF, color);
  prog->setUniform(KC_LIGHT_UNIF, kc);
  prog->setUniform(KL_LIGHT_UNIF, kl);
  prog->setUniform(KQ_LIGHT_UNIF, kq);
  prog->setUniform(AMB_LIGHT_UNIF, ambientCoef);


}


void light::remove()
{

}
