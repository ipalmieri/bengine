#include "berror.h"

using namespace std;
using namespace tools;
using namespace engine;


void engine::bCheckError()
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    string err = bPrintError(error);

    throw std::runtime_error(err);
  }
}


string engine::bPrintError(GLenum errorCode)
{
  std::ostringstream temp;

  if (errorCode != GL_NO_ERROR) {
    std::string error = "unknown error";
    std::string description  = "no description";

    // Decode the error code
    switch (errorCode) {
      case GL_INVALID_ENUM : {
        error = "GL_INVALID_ENUM";
        description =
          "an unacceptable value has been specified for an enumerated argument";
        break;
      }

      case GL_INVALID_VALUE : {
        error = "GL_INVALID_VALUE";
        description = "a numeric argument is out of range";
        break;
      }

      case GL_INVALID_OPERATION : {
        error = "GL_INVALID_OPERATION";
        description = "the specified operation is not allowed in the current state";
        break;
      }

      case GL_STACK_OVERFLOW : {
        error = "GL_STACK_OVERFLOW";
        description = "this command would cause a stack overflow";
        break;
      }

      case GL_STACK_UNDERFLOW : {
        error = "GL_STACK_UNDERFLOW";
        description = "this command would cause a stack underflow";
        break;
      }

      case GL_OUT_OF_MEMORY : {
        error = "GL_OUT_OF_MEMORY";
        description = "there is not enough memory left to execute the command";
        break;
      }

      case GL_INVALID_FRAMEBUFFER_OPERATION_EXT : {
        error = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
        description =
          "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
        break;
      }
    }


    temp << "OpenGL Error: "  << error << ", " << description;
  }


  return temp.str();
}
