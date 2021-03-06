#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "edefs.h"

namespace engine {
class frustum;

class camera
{
 public:
  camera();
  ~camera();

  void addYaw(const Radian& delta);
  void addPitch(const Radian& delta);
  void addRoll(const Radian& delta);

  void moveForward(const Real& delta);
  void moveRight(const Real& delta);
  void moveUpward(const Real& delta);

  void setPosition(const Real& x, const Real& y, const Real& z);

  void lookAt(const tools::vector3& eye,
              const tools::vector3& center,
              const tools::vector3& up);

  inline tools::transMatrix matrix()
  {
    return projection()*view();
  }
  inline tools::transMatrix view()
  {
    return _matrix;
  }
  tools::transMatrix projection();

  inline frustum* viewFrustum()
  {
    return _frustum;
  }


 protected:

  frustum* _frustum;

  tools::transMatrix _matrix;

  tools::vector3 _position;

  tools::vector3 _frontVector;
  tools::vector3 _upVector;
  tools::vector3 _rightVector;

  void updateMatrix();

};
}

#endif
