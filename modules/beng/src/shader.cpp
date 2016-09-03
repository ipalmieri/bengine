#include <fstream>
#include <sstream>
#include "shader.h"

using namespace std;
using namespace tools;
using namespace engine;

shader::shader(const string& code, const GLenum& type) : _object(0)
{

  _object = glCreateShader(type);

  if (_object == 0) {
    throw runtime_error("glCreateShader failed");
  }


  const char* scode = code.c_str();

  glShaderSource(_object, 1, (const GLchar**)&scode, NULL);

  glCompileShader(_object);

  //throw exception if compile error occurred
  GLint status;

  glGetShaderiv(_object, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    std::string msg("Compile failure in shader:\n");

    GLint infoLogLength;

    glGetShaderiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);

    char* strInfoLog = new char[infoLogLength + 1];

    glGetShaderInfoLog(_object, infoLogLength, NULL, strInfoLog);

    msg += strInfoLog;

    delete[] strInfoLog;

    glDeleteShader(_object);
    _object = 0;

    //throw std::runtime_error(msg);
    logger::logMsg(msg, LGR_ERROR);
  }

}

shader::~shader()
{
  glDeleteShader(_object);

  _object = 0;
}

shader* shader::shaderFromFile(const string& filename, const GLenum& type)
{
  ifstream file;
  std::stringstream buffer;

  string filepath = SHADER_PATH + filename;

  file.open(filepath.c_str(), std::ios::in | std::ios::binary);

  if (!file.is_open()) {
    //throw std::runtime_error(std::string("Failed to open file: ") + filePath);
    logger::logMsg("Failed to open shader file: " + filepath, LGR_ERROR);
  } else {
    buffer << file.rdbuf();
  }

  shader* ret = new shader(buffer.str(), type);

  return ret;
}
