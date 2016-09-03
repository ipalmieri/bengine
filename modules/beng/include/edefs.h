#ifndef __EDEFS_H__
#define __EDEFS_H__

#include <GL/glew.h>

#include <stdexcept>
#include <cassert>


#include "tools.h"


namespace engine {
typedef float Real;
typedef float Radian;
}


#define SHADER_PATH "modules/beng/shaders/"
#define TEXTURE_PATH "data/beng/"

#define DEF_VSHADER "default.vert"
#define DEF_FSHADER "default.frag"

//camera setup
#define DEF_FOV 60.0
#define DEF_ASPECT 1.33
#define DEF_NEAR 1
#define DEF_FAR 100

#define DEF_COLOR tools::vector4(0.5f, 0.5f, 0.5f, 1.0f)
#define DEF_GAMMA tools::vector3(1.0f, 1.0f, 1.0f)

#endif
