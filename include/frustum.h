#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include <cmath>
#include "edefs.h"

namespace engine {
class frustum
{
  friend class camera;

 public:

  void setParameters(const Real& pleft, const Real& pright,
                     const Real& pbottom, const Real& ptop,
                     const Real& pnear, const Real& pfar);

  void setPerspective(const Real& fovy, const Real& aspect,
                      const Real& near, const Real& far);


  Real left;
  Real right;
  Real bottom;
  Real top;
  Real near;
  Real far;


  inline Real aspectRatio()
  {
    return right/top;
  }
  inline Real fieldOfView()
  {
    return atan(top/near) * 360.0f / M_PI;
  }


  tools::transMatrix projection();


 protected:

  frustum(const Real& pleft, const Real& pright,
          const Real& pbottom, const Real& ptop,
          const Real& pnear, const Real& pfar)
  {
    setParameters(pleft, pright, pbottom, ptop, pnear, pfar);
  }

  frustum(const Real& fovy, const Real& aspect,
          const Real& pnear, const Real& pfar)
  {
    setPerspective(fovy, aspect, pnear, pfar);
  }

  ~frustum() {}

};
}
#endif
