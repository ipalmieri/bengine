#include "engnode.h"
#include "mesh.h"
#include "material.h"
#include "edefs.h"

using namespace engine;
using namespace tools;
using namespace std;

engnode::engnode(engnode *parent) : tnode(parent)
{
   matrix = transMatrix(Matrix4::IDENTITY);
}

engnode::~engnode()
{

}

void engnode::draw(material *mat, program *prog)
{

   for (vector<engset>::iterator it = engsets.begin(); it != engsets.end(); ++it)
   {
      if (it->mater == mat && it->prog == prog)
      {
	 (it->meshe)->draw();
      }
   }

}

void engnode::addEngset(mesh *me, material *mat, program *prog)
{
   engset eset;

   eset.meshe = me;
   eset.mater = mat;
   eset.prog = prog;

   engsets.push_back(eset);
}
