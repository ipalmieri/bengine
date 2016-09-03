#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "singleton.h"
#include "edefs.h"
#include "algebra.h"

#define BENG_MSTACK 1024

namespace engine {
class camera;
class viewport;
class light;
class material;
class mesh;
class material;
class engnode;
class shader;
class program;
class texture;

class renderer
{
 public:
  friend class tools::singleton<renderer>;

  void init();
  void stop();

  void drawScene();

  void resetScreen(const int& x, const int& y, const unsigned& width,
                   const unsigned& height);


  camera* activeCamera()
  {
    return _camera;
  }
  viewport* activeViewport()
  {
    return _vport;
  }
  engnode* rootNode()
  {
    return _rootNode;
  }

  void addNode(engnode* node, engnode* parend=NULL);

  //resource management - fix this
  material* createMaterial();
  mesh* createMesh();
  light* createLight(const tools::vector4& pos);
  shader* createVertexShader(const std::string& filename);
  shader* createFragmentShader(const std::string& filename);
  program* createProgram(const std::vector<shader*>& shaders);
  texture* createTexture(const std::string& filename);
  //--


  void pushMatrix(const tools::transMatrix& tmat);
  void popMatrix();


 protected:

  renderer();
  ~renderer();

  viewport* _vport;
  camera* _camera;

  std::vector<light*> _lights;
  std::vector<material*> _materials;
  std::vector<mesh*> _meshes;
  std::vector<texture*> _textures;
  std::vector<shader*> _shaders;
  std::vector<program*> _programs;


  tools::vector3 _gamma;

  engnode* _rootNode;

  std::vector<tools::transMatrix> _mstack;

  void drawNode(engnode* nd, material* mat, program* prog);

};

typedef tools::singleton<renderer> rendererSingleton;

}

#endif
