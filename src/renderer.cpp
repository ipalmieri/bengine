#include "beng.h"

using namespace std;
using namespace tools;
using namespace engine;

renderer::renderer()
{
  //fix this
  _vport = new viewport(0, 0, 640, 480);
  _camera = new camera();

  _rootNode = new engnode(NULL);

  _mstack.push_back(matrix4::IDENTITY);

  init();
}

renderer::~renderer()
{
  delete _vport;
  delete _camera;

  //delete lights
  for (vector<light*>::iterator it = _lights.begin(); it != _lights.end(); ++it) {
    delete (*it);
  }

  //delete materials
  for (vector<material*>::iterator it = _materials.begin();
       it != _materials.end(); ++it) {
    delete (*it);
  }

  //delete meshes
  for (vector<mesh*>::iterator it = _meshes.begin(); it != _meshes.end(); ++it) {
    delete (*it);
  }

  //delete shaders
  for (vector<shader*>::iterator it = _shaders.begin(); it != _shaders.end();
       ++it) {
    delete (*it);
  }

  //delete programs
  for (vector<program*>::iterator it = _programs.begin(); it != _programs.end();
       ++it) {
    delete (*it);
  }

  //delete textures
  for (vector<texture*>::iterator it = _textures.begin();  it != _textures.end();
       ++it) {
    delete (*it);
  }

  //delete engnodes
  delete _rootNode;
}

void renderer::init()
{
  glEnable(GL_DEPTH_TEST);


  _vport->apply();

  //fix this - this belongs to the outside world
  _camera->lookAt(vector3(10, 0, 0), vector3(0, 0, 0), vector3(0, 0, 1));

  _gamma = DEF_GAMMA;


  // fix this - use multipass
  glEnable(GL_BLEND);


}


void renderer::stop()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
}

void renderer::drawNode(engnode* nd, material* mat, program* prog)
{

  pushMatrix(nd->matrix);

  prog->setUniform(MODEL_UNIF, _mstack.back());


  nd->draw(mat, prog);

  tnode::tnodeVector cvec = nd->children();

  for (tnode::tnodeVector::iterator it = cvec.begin(); it != cvec.end(); ++it) {
    drawNode((engnode*) *it, mat, prog);
  }

  popMatrix();
}

void renderer::drawScene()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  for (vector<program*>::iterator pg = _programs.begin(); pg != _programs.end();
       ++pg) {
    program* prog = *pg;

    prog->apply();

    //set shader uniforms
    prog->setUniform(PROJ_UNIF, _camera->projection());
    prog->setUniform(VIEW_UNIF, _camera->view());
    prog->setUniform(GAMMA_UNIF, _gamma);

    for (vector<material*>::iterator mt = _materials.begin();
         mt != _materials.end(); ++mt) {

      material* mat = *mt;

      mat->apply(prog);

      // fix this - use deferred shading
      glBlendFunc(GL_ONE, GL_ZERO);
      glDepthFunc(GL_LEQUAL);

      for (unsigned i = 0; i < _lights.size(); i++) {
        _lights[i]->apply(prog);

        if (i > 0) {
          glBlendFunc(GL_ONE, GL_ONE);
          glDepthFunc(GL_LEQUAL);
        }

        drawNode(_rootNode, mat, prog);


        _lights[i]->remove();
      }


      mat->remove();

    }

    prog->remove();
  }

}

light* renderer::createLight(const vector4& pos)
{
  light* ln = new light(pos);

  _lights.push_back(ln);

  return ln;
}

mesh* renderer::createMesh()
{
  mesh* ms = new mesh();

  _meshes.push_back(ms);

  return ms;
}

material* renderer::createMaterial()
{
  material* mt = new material();

  _materials.push_back(mt);

  return mt;
}

void renderer::pushMatrix(const transMatrix& tmat)
{
  if (_mstack.size() <= BENG_MSTACK) {
    _mstack.push_back(_mstack.back() * tmat);
  } else {
    logger::logMsg("Renderer matrix stack is full.", LGR_ERROR);
  }
}

void renderer::popMatrix()
{
  if (_mstack.size() > 1) {
    _mstack.pop_back();
  } else {
    logger::logMsg("Renderer matrix stack is empty.", LGR_ERROR);
  }

}

shader* renderer::createVertexShader(const std::string& filename)
{
  shader* ret = shader::shaderFromFile(filename, GL_VERTEX_SHADER);

  _shaders.push_back(ret);

  return ret;
}

shader* renderer::createFragmentShader(const std::string& filename)
{
  shader* ret = shader::shaderFromFile(filename, GL_FRAGMENT_SHADER);

  _shaders.push_back(ret);

  return ret;
}

program* renderer::createProgram(const std::vector<shader*>& shaders)
{
  program* ret = new program(shaders);

  _programs.push_back(ret);

  return ret;
}

texture* renderer::createTexture(const std::string& filename)
{
  texture* ret = texture::loadTextureFromFile(filename);

  _textures.push_back(ret);

  return ret;
}

void renderer::resetScreen(const int& x, const int& y, const unsigned& width,
                           const unsigned& height)
{
  _vport->reset(x, y, width, height);

  frustum* frust = _camera->viewFrustum();

  frust->setPerspective(frust->fieldOfView(), (Real) width / (Real) height,
                        frust->near, frust->far);
}
