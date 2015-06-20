#ifndef __BERROR_H__
#define __BERROR_H__

#include <sstream>
#include "edefs.h"

namespace engine
{

   void bCheckError();

   std::string bPrintError(GLenum errorCode);

}

#endif
