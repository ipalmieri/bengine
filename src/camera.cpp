#include "camera.h"
#include "frustum.h"

using namespace tools;
using namespace engine;

camera::camera()
{
   _frustum = new frustum(DEF_FOV, DEF_ASPECT, DEF_NEAR, DEF_FAR);

   _position = Vector3::ZERO;

   _frontVector = -Vector3::Z;
   _upVector = Vector3::Y;
   _rightVector = _frontVector^_upVector;

   updateMatrix();
}

camera::~camera()
{
   delete _frustum;
}

void camera::updateMatrix()
{
   //Builds Rotation Matrix
   _matrix[0][0] = _rightVector[0];
   _matrix[0][1] = _rightVector[1];
   _matrix[0][2] = _rightVector[2];

   _matrix[1][0] = _upVector[0];
   _matrix[1][1] = _upVector[1];
   _matrix[1][2] = _upVector[2];

   _matrix[2][0] = -_frontVector[0];
   _matrix[2][1] = -_frontVector[1];
   _matrix[2][2] = -_frontVector[2];
   
   //Adds Translation
   _matrix[0][3] = -(_position[0]*_matrix[0][0] + _position[1]*_matrix[0][1] + _position[2]*_matrix[0][2]);
   _matrix[1][3] = -(_position[0]*_matrix[1][0] + _position[1]*_matrix[1][1] + _position[2]*_matrix[1][2]);
   _matrix[2][3] = -(_position[0]*_matrix[2][0] + _position[1]*_matrix[2][1] + _position[2]*_matrix[2][2]);
   
}

void camera::addYaw(const Radian &delta)
{
   Quaternion q = Quaternion(_upVector, -delta);
   _frontVector = q.rotate(_frontVector);
   _rightVector = _frontVector^_upVector;

    updateMatrix();
}

void camera::addPitch(const Radian &delta)
{
   Quaternion q = Quaternion(_rightVector, delta);
   _frontVector = q.rotate(_frontVector);
   _upVector = _rightVector^_frontVector;
   
   updateMatrix();
}

void camera::addRoll(const Radian &delta)
{
   Quaternion q = Quaternion(_frontVector, delta);
   _upVector = q.rotate(_upVector);
   _rightVector = _frontVector^_upVector;

   updateMatrix();
}

void camera::moveForward(const Real &delta)
{
   _position += _frontVector*delta;
   
   updateMatrix();
}

void camera::moveRight(const Real &delta)
{
   _position += _rightVector*delta;
   
   updateMatrix();
}

void camera::moveUpward(const Real &delta)
{
   _position += _upVector*delta;

   updateMatrix();
}

void camera::setPosition(const Real &x, const Real &y, const Real &z)
{
   _position = tools::Vector3(x, y, z);
   updateMatrix();
}

void camera::lookAt(const tools::Vector3 &eye,
	    const tools::Vector3 &center,
	    const tools::Vector3 &up)
{
   _frontVector = normalize(center - eye);

   _upVector = normalize(up);

   _rightVector = _frontVector^_upVector;

   _position = eye;

   updateMatrix();
}

transMatrix camera::projection()
{
   return _frustum->projection();
}



