#ifndef __ENGNODE_H__
#define __ENGNODE_H__

#include "algebra.h"
#include "tree/tnode.h"

namespace engine {
class material;
class mesh;
class program;

class engset
{
 public:
  engset()
  {
    meshe = NULL;
    mater = NULL;
    prog = NULL;
  };
  ~engset() {};

  mesh* meshe;
  material* mater;
  program* prog;

};



class engnode : public tools::tnode
{
 public:
  engnode(engnode* parent);
  ~engnode();

  void draw(material* mat, program* prog);

  void addEngset(mesh* me, material* mat = NULL, program* prog = NULL);

  tools::transMatrix matrix;
  std::vector<engset> engsets;

};

}

#endif
