#include "frustum.h"
#include <algorithm>
#include "algebra.h"

using namespace std;
using namespace tools;
using namespace engine;

void frustum::setParameters(const Real& pleft, const Real& pright,
                            const Real& pbottom, const Real& ptop,
                            const Real& pnear, const Real& pfar)
{
  left = pleft;
  right = pright;
  bottom = pbottom;
  top = ptop;
  near = pnear;
  far = pfar;

}

void frustum::setPerspective(const Real& fovy, const Real& aspect,
                             const Real& pnear, const Real& pfar)
{
  Real fov = min(max(fovy, 0.0f), 180.0f);

  top = pnear*tan(0.5f * fov * M_PI / 180.0f);
  bottom = -top;

  right = top*aspect;
  left = -right;

  near = pnear;
  far = pfar;

}

transMatrix frustum::projection()
{
  transMatrix pmat;

  assert(left != right);
  assert(far != near);
  assert(top != bottom);

  pmat = matrix4(2.0f*near/(right-left), 0.0, (right+left)/(right-left), 0.0,
                 0.0, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0,
                 0.0, 0.0, -(far+near)/(far-near), -2.0f*far*near/(far-near),
                 0.0, 0.0, -1.0f, 0.0);

  return pmat;
}


