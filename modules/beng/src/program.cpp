#include "program.h"
#include "shader.h"

using namespace std;
using namespace tools;
using namespace engine;

program::program(const std::vector<shader*>& shaders) : _object(0)
{
  if (shaders.size() <= 0) {
    throw std::runtime_error("No shaders were provided to create the program");
  }


  _object = glCreateProgram();

  if (_object == 0) {
    throw std::runtime_error("glCreateProgram failed");
  }

  for (unsigned i = 0; i < shaders.size(); ++i) {
    glAttachShader(_object, shaders[i]->object());
  }

  //attribute naming
  glBindAttribLocation(_object, LOC_VERTEX, ATT_VERTEX);
  glBindAttribLocation(_object, LOC_NORMAL, ATT_NORMAL);
  glBindAttribLocation(_object, LOC_TEXTUR, ATT_TEXCOR);



  glLinkProgram(_object);

  for (unsigned i = 0; i < shaders.size(); ++i) {
    glDetachShader(_object, shaders[i]->object());
  }


  //check status of compiling/linking
  GLint status;

  glGetProgramiv(_object, GL_LINK_STATUS, &status);

  if (status == GL_FALSE) {

    std::string msg("Program linking failure:");

    GLint infoLogLength;

    glGetProgramiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);

    char* strInfoLog = new char[infoLogLength + 1];

    glGetProgramInfoLog(_object, infoLogLength, NULL, strInfoLog);

    msg += strInfoLog;

    delete[] strInfoLog;

    glDeleteProgram(_object);
    _object = 0;

    logger::logMsg(msg, LGR_ERROR);
    //throw std::runtime_error(msg);
  }

}

program::~program()
{
  glUseProgram(0);

  if (_object != 0) {
    glDeleteProgram(_object);
  }
}

void program::apply() const
{
  glUseProgram(_object);
}

bool program::isApplied() const
{
  GLint currentProgram = 0;

  glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

  return (currentProgram == (GLint)_object);
}

void program::remove() const
{
  if (isApplied()) {
    glUseProgram(0);
  }
}


GLint program::attrib(const GLchar* name) const
{
  return glGetAttribLocation(_object, name);
}

GLint program::uniform(const GLchar* name) const
{
  return glGetUniformLocation(_object, name);
}

void program::setUniform(const GLchar* name, const int& value)
{
  GLint uname = uniform(name);

  if (_object != 0 && uname != -1) {
    glProgramUniform1i(_object, uname, value);
  }
}

void program::setUniform(const GLchar* name, const Real& value)
{
  GLint uname = uniform(name);

  if (_object != 0 && uname != -1) {
    if (sizeof(tools::Real) == sizeof(double)) {
      glProgramUniform1d(_object, uname, value);
    } else {
      glProgramUniform1f(_object, uname, value);
    }
  }
}

void program::setUniform(const GLchar* name, const vector3& v)
{
  GLint uname = uniform(name);

  if (_object != 0 && uname != -1) {
    if (sizeof(tools::Real) == sizeof(double)) {
      glProgramUniform3d(_object, uname, v[0], v[1], v[2]);
    } else {
      glProgramUniform3f(_object, uname, v[0], v[1], v[2]);
    }
  }
}

void program::setUniform(const GLchar* name, const vector4& v)
{
  GLint uname = uniform(name);

  if (_object != 0 && uname != -1) {
    if (sizeof(tools::Real) == sizeof(double)) {
      glProgramUniform4d(_object, uname, v[0], v[1], v[2], v[3]);
    } else {
      glProgramUniform4f(_object, uname, v[0], v[1], v[2], v[3]);
    }
  }
}

void program::setUniform(const GLchar* name, const transMatrix& m,
                         GLboolean transpose)
{
  GLint uname = uniform(name);

  if (_object != 0 && uname != -1) {
    if (sizeof(tools::Real) == sizeof(double)) {
      glProgramUniformMatrix4dv(_object, uname, 1, transpose,
                                (GLdouble*) m.getData());
    } else {
      glProgramUniformMatrix4fv(_object, uname, 1, transpose, (GLfloat*) m.getData());
    }
  }
}


