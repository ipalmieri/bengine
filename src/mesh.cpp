#include "stdlib.h"
#include "mesh.h"
#include "program.h"
#include "algebra.h"

using namespace engine;
using namespace tools;

mesh::mesh()
{
  _ibuffer = 0;
  _vbuffer = 0;
  _varray = 0;

  _vcount = 0;
  _icount = 0;

  glGenVertexArrays(1, &_varray);

  glGenBuffers(1, &_ibuffer);
  glGenBuffers(1, &_vbuffer);

  if (_ibuffer == 0 || _vbuffer == 0 || _varray == 0) {
    throw std::runtime_error("Mesh glGen* failed");
  }

}

mesh::~mesh()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //glInvalidateBufferData(_ibuffer);
  //glInvalidateBufferData(_vbuffer);

  glDeleteBuffers(1, &_ibuffer);
  glDeleteBuffers(1, &_vbuffer);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &_varray);
}

void mesh::draw() const
{
  if (_vcount > 0 && _icount > 0) {
    glBindVertexArray(_varray);

    glBindBuffer(GL_ARRAY_BUFFER, _vbuffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuffer);


    glDrawElements(GL_TRIANGLES, _icount*3, GL_UNSIGNED_INT, (void*)0);

  }

}

void mesh::setVertexBuffer(mvertex* buff, const unsigned& count)
{

  glBindVertexArray(_varray);

  glBindBuffer(GL_ARRAY_BUFFER, _vbuffer);

  glBufferData(GL_ARRAY_BUFFER, sizeof(mvertex)*count, buff, GL_STATIC_DRAW);


  //vertex packing
  //fix this
  glEnableVertexAttribArray(LOC_VERTEX);
  glVertexAttribPointer(LOC_VERTEX, TAM_VERTEX, GL_FLOAT, GL_FALSE,
                        sizeof(mvertex), (GLvoid*) 0);

  glEnableVertexAttribArray(LOC_NORMAL);
  glVertexAttribPointer(LOC_NORMAL, TAM_NORMAL, GL_FLOAT, GL_FALSE,
                        sizeof(mvertex), (GLvoid*) (sizeof(float)*TAM_VERTEX));

  glEnableVertexAttribArray(LOC_TEXTUR);
  glVertexAttribPointer(LOC_TEXTUR, TAM_TEXTUR, GL_FLOAT, GL_FALSE,
                        sizeof(mvertex), (GLvoid*) (sizeof(float)*(TAM_VERTEX + TAM_NORMAL)));


  glBindVertexArray(0);

  _vcount = count;
}

void mesh::setIndexBuffer(mtriangle* buff, const unsigned& count)
{

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mtriangle)*count, buff,
               GL_STATIC_DRAW);

  _icount = count;

}

void engine::createCubeMesh(mesh* ms, const float& size)
{
  float x = size*0.5f;

  mvertex* vbuff = (mvertex*) malloc(sizeof(mvertex)*24);
  mtriangle* ibuff = (mtriangle*) malloc(sizeof(mtriangle)*12);

  //x = 1
  vbuff[0].vertex[0] = x;
  vbuff[0].vertex[1] = -x;
  vbuff[0].vertex[2] = x;
  vbuff[0].vertex[3] = 1.0f;
  vbuff[0].texcoord[0] = 0.0f;
  vbuff[0].texcoord[1] = 1.0f;

  vbuff[1].vertex[0] = x;
  vbuff[1].vertex[1] = x;
  vbuff[1].vertex[2] = x;
  vbuff[1].vertex[3] = 1.0f;
  vbuff[1].texcoord[0] = 1.0f;
  vbuff[1].texcoord[1] = 1.0f;

  vbuff[2].vertex[0] = x;
  vbuff[2].vertex[1] = x;
  vbuff[2].vertex[2] = -x;
  vbuff[2].vertex[3] = 1.0f;
  vbuff[2].texcoord[0] = 1.0f;
  vbuff[2].texcoord[1] = 0.0f;

  vbuff[3].vertex[0] = x;
  vbuff[3].vertex[1] = -x;
  vbuff[3].vertex[2] = -x;
  vbuff[3].vertex[3] = 1.0f;
  vbuff[3].texcoord[0] = 0.0f;
  vbuff[3].texcoord[1] = 0.0f;

  //x = -1
  vbuff[4].vertex[0] = -x;
  vbuff[4].vertex[1] = x;
  vbuff[4].vertex[2] = x;
  vbuff[4].vertex[3] = 1.0f;
  vbuff[4].texcoord[0] = 0.0f;
  vbuff[4].texcoord[1] = 1.0f;

  vbuff[5].vertex[0] = -x;
  vbuff[5].vertex[1] = -x;
  vbuff[5].vertex[2] = x;
  vbuff[5].vertex[3] = 1.0f;
  vbuff[5].texcoord[0] = 1.0f;
  vbuff[5].texcoord[1] = 1.0f;

  vbuff[6].vertex[0] = -x;
  vbuff[6].vertex[1] = -x;
  vbuff[6].vertex[2] = -x;
  vbuff[6].vertex[3] = 1.0f;
  vbuff[6].texcoord[0] = 1.0f;
  vbuff[6].texcoord[1] = 0.0f;

  vbuff[7].vertex[0] = -x;
  vbuff[7].vertex[1] = x;
  vbuff[7].vertex[2] = -x;
  vbuff[7].vertex[3] = 1.0f;
  vbuff[7].texcoord[0] = 0.0f;
  vbuff[7].texcoord[1] = 0.0f;

  //y = 1
  vbuff[8].vertex[0] = x;
  vbuff[8].vertex[1] = x;
  vbuff[8].vertex[2] = x;
  vbuff[8].vertex[3] = 1.0f;
  vbuff[8].texcoord[0] = 0.0f;
  vbuff[8].texcoord[1] = 1.0f;

  vbuff[9].vertex[0] = -x;
  vbuff[9].vertex[1] = x;
  vbuff[9].vertex[2] = x;
  vbuff[9].vertex[3] = 1.0f;
  vbuff[9].texcoord[0] = 1.0f;
  vbuff[9].texcoord[1] = 1.0f;

  vbuff[10].vertex[0] = -x;
  vbuff[10].vertex[1] = x;
  vbuff[10].vertex[2] = -x;
  vbuff[10].vertex[3] = 1.0f;
  vbuff[10].texcoord[0] = 1.0f;
  vbuff[10].texcoord[1] = 0.0f;

  vbuff[11].vertex[0] = x;
  vbuff[11].vertex[1] = x;
  vbuff[11].vertex[2] = -x;
  vbuff[11].vertex[3] = 1.0f;
  vbuff[11].texcoord[0] = 0.0f;
  vbuff[11].texcoord[1] = 0.0f;

  //y = -1
  vbuff[12].vertex[0] = -x;
  vbuff[12].vertex[1] = -x;
  vbuff[12].vertex[2] = x;
  vbuff[12].vertex[3] = 1.0f;
  vbuff[12].texcoord[0] = 0.0f;
  vbuff[12].texcoord[1] = 1.0f;

  vbuff[13].vertex[0] = x;
  vbuff[13].vertex[1] = -x;
  vbuff[13].vertex[2] = x;
  vbuff[13].vertex[3] = 1.0f;
  vbuff[13].texcoord[0] = 1.0f;
  vbuff[13].texcoord[1] = 1.0f;

  vbuff[14].vertex[0] = x;
  vbuff[14].vertex[1] = -x;
  vbuff[14].vertex[2] = -x;
  vbuff[14].vertex[3] = 1.0f;
  vbuff[14].texcoord[0] = 1.0f;
  vbuff[14].texcoord[1] = 0.0f;

  vbuff[15].vertex[0] = -x;
  vbuff[15].vertex[1] = -x;
  vbuff[15].vertex[2] = -x;
  vbuff[15].vertex[3] = 1.0f;
  vbuff[15].texcoord[0] = 0.0f;
  vbuff[15].texcoord[1] = 0.0f;

  //z = 1
  vbuff[16].vertex[0] = x;
  vbuff[16].vertex[1] = -x;
  vbuff[16].vertex[2] = x;
  vbuff[16].vertex[3] = 1.0f;
  vbuff[16].texcoord[0] = 0.0f;
  vbuff[16].texcoord[1] = 1.0f;

  vbuff[17].vertex[0] = -x;
  vbuff[17].vertex[1] = -x;
  vbuff[17].vertex[2] = x;
  vbuff[17].vertex[3] = 1.0f;
  vbuff[17].texcoord[0] = 1.0f;
  vbuff[17].texcoord[1] = 1.0f;

  vbuff[18].vertex[0] = -x;
  vbuff[18].vertex[1] = x;
  vbuff[18].vertex[2] = x;
  vbuff[18].vertex[3] = 1.0f;
  vbuff[18].texcoord[0] = 1.0f;
  vbuff[18].texcoord[1] = 0.0f;

  vbuff[19].vertex[0] = x;
  vbuff[19].vertex[1] = x;
  vbuff[19].vertex[2] = x;
  vbuff[19].vertex[3] = 1.0f;
  vbuff[19].texcoord[0] = 0.0f;
  vbuff[19].texcoord[1] = 0.0f;

  //z = -1
  vbuff[20].vertex[0] = -x;
  vbuff[20].vertex[1] = -x;
  vbuff[20].vertex[2] = -x;
  vbuff[20].vertex[3] = 1.0f;
  vbuff[20].texcoord[0] = 0.0f;
  vbuff[20].texcoord[1] = 1.0f;

  vbuff[21].vertex[0] = x;
  vbuff[21].vertex[1] = -x;
  vbuff[21].vertex[2] = -x;
  vbuff[21].vertex[3] = 1.0f;
  vbuff[21].texcoord[0] = 1.0f;
  vbuff[21].texcoord[1] = 1.0f;

  vbuff[22].vertex[0] = x;
  vbuff[22].vertex[1] = x;
  vbuff[22].vertex[2] = -x;
  vbuff[22].vertex[3] = 1.0f;
  vbuff[22].texcoord[0] = 1.0f;
  vbuff[22].texcoord[1] = 0.0f;

  vbuff[23].vertex[0] = -x;
  vbuff[23].vertex[1] = x;
  vbuff[23].vertex[2] = -x;
  vbuff[23].vertex[3] = 1.0f;
  vbuff[23].texcoord[0] = 0.0f;
  vbuff[23].texcoord[1] = 0.0f;

  //x = 1
  ibuff[0].v0 = 0;
  ibuff[0].v1 = 1;
  ibuff[0].v2 = 2;

  ibuff[1].v0 = 0;
  ibuff[1].v1 = 2;
  ibuff[1].v2 = 3;

  //x = -1
  ibuff[2].v0 = 4;
  ibuff[2].v1 = 5;
  ibuff[2].v2 = 6;

  ibuff[3].v0 = 4;
  ibuff[3].v1 = 6;
  ibuff[3].v2 = 7;

  //y = 1
  ibuff[4].v0 = 8;
  ibuff[4].v1 = 9;
  ibuff[4].v2 = 10;

  ibuff[5].v0 = 8;
  ibuff[5].v1 = 10;
  ibuff[5].v2 = 11;

  //y = -1
  ibuff[6].v0 = 12;
  ibuff[6].v1 = 13;
  ibuff[6].v2 = 14;

  ibuff[7].v0 = 12;
  ibuff[7].v1 = 14;
  ibuff[7].v2 = 15;

  //z = 1
  ibuff[8].v0 = 16;
  ibuff[8].v1 = 17;
  ibuff[8].v2 = 18;

  ibuff[9].v0 = 16;
  ibuff[9].v1 = 18;
  ibuff[9].v2 = 19;

  //z = -1
  ibuff[10].v0 = 20;
  ibuff[10].v1 = 21;
  ibuff[10].v2 = 22;

  ibuff[11].v0 = 20;
  ibuff[11].v1 = 22;
  ibuff[11].v2 = 23;


  //calculate normals
  for (unsigned i = 0; i < 12; i++) {
    mvertex mv0 = vbuff[ibuff[i].v0];
    mvertex mv1 = vbuff[ibuff[i].v1];
    mvertex mv2 = vbuff[ibuff[i].v2];

    vector3 vec0 = vector3(mv0.vertex[0], mv0.vertex[1], mv0.vertex[2]);
    vector3 vec1 = vector3(mv1.vertex[0], mv1.vertex[1], mv1.vertex[2]);
    vector3 vec2 = vector3(mv2.vertex[0], mv2.vertex[1], mv2.vertex[2]);

    vector3 norm = (vec1 - vec0) ^ (vec2 - vec0);

    vbuff[ibuff[i].v0].normal[0] = vbuff[ibuff[i].v1].normal[0] =
                                     vbuff[ibuff[i].v2].normal[0] = -norm[0];
    vbuff[ibuff[i].v0].normal[1] = vbuff[ibuff[i].v1].normal[1] =
                                     vbuff[ibuff[i].v2].normal[1] = -norm[1];
    vbuff[ibuff[i].v0].normal[2] = vbuff[ibuff[i].v1].normal[2] =
                                     vbuff[ibuff[i].v2].normal[2] = -norm[2];

  }

  if (ms) {
    ms->setVertexBuffer(vbuff, 24);
    ms->setIndexBuffer(ibuff, 12);
  }

  free(vbuff);
  free(ibuff);

}

void engine::createPlaneMesh(mesh* ms, const unsigned& width,
                             const unsigned& length, const float& unit)
{
  unsigned vcount = (width + 1)*(length + 1);
  unsigned icount = 2*width*length;

  mvertex* vbuff = (mvertex*) malloc(sizeof(mvertex)*vcount);
  mtriangle* ibuff = (mtriangle*) malloc(sizeof(mtriangle)*icount);


  float size_x = unit * (float) width;
  float size_y = unit * (float) length;

  unsigned ind = 0;

  for (unsigned i = 0; i < width + 1; i++) {
    for (unsigned j = 0; j < length + 1; j++) {

      vbuff[ind].vertex[0] = unit * (float) i - size_x / 2.0f;
      vbuff[ind].vertex[1] = unit * (float) j - size_y / 2.0f;
      vbuff[ind].vertex[2] = 0.0f;
      vbuff[ind].vertex[3] = 1.0f;

      vbuff[ind].normal[0] = 0.0f;
      vbuff[ind].normal[1] = 0.0f;
      vbuff[ind].normal[2] = 1.0f;

      vbuff[ind].texcoord[0] = ((float) i) / (float) width;
      vbuff[ind].texcoord[1] = ((float) j) / (float) length;


      ind++;
    }

  }


  ind = 0;

  for (unsigned i = 0; i < width; i++) {
    for (unsigned j = 0; j < length; j++) {

      ibuff[ind].v0 = i * (length + 1) + j;
      ibuff[ind].v1 = (i + 1) * (length + 1) + j;
      ibuff[ind].v2 = i * (length + 1) + j + 1;

      ibuff[ind + 1].v0 = i * (length + 1) + j + 1;
      ibuff[ind + 1].v1 = (i + 1) * (length + 1) + j;
      ibuff[ind + 1].v2 = (i + 1) * (length + 1) + j + 1;

      ind = ind + 2;

    }
  }


  if (ms) {
    ms->setVertexBuffer(vbuff, vcount);
    ms->setIndexBuffer(ibuff, icount);
  }

  free(vbuff);
  free(ibuff);

}


void engine::createSphereMesh(mesh* ms, const float& radius,
                              const unsigned& rings, const unsigned& sectors)
{
  unsigned vcount = (sectors + 1) * (rings - 1) + 2 * sectors;
  unsigned icount = 2*sectors + 2 * sectors * (rings - 2);

  mvertex* vbuff = (mvertex*) malloc(sizeof(mvertex)*vcount);
  mtriangle* ibuff = (mtriangle*) malloc(sizeof(mtriangle)*icount);

  float delta_x = 1.0f / (float) sectors;
  float delta_y = 1.0f / (float) rings;

  unsigned ind = 0;

  // VERTICES

  // superior cap
  for (unsigned j = 0; j < sectors; j++) {
    vbuff[ind].vertex[0] = 0.0f;
    vbuff[ind].vertex[1] = 0.0f;
    vbuff[ind].vertex[2] = radius;
    vbuff[ind].vertex[3] = 1.0f;

    vbuff[ind].normal[0] = 0.0f;
    vbuff[ind].normal[1] = 0.0f;
    vbuff[ind].normal[2] = 1.0f;

    vbuff[ind].texcoord[0] = delta_x / 2.0f + j * delta_x;
    vbuff[ind].texcoord[1] = 1.0f;

    ind++;
  }

  // middle sphere
  for (unsigned i = 0; i < rings - 1; i++) {
    for (unsigned j = 0; j < sectors + 1; j++) {
      float x = sin(M_PI * ((float) i + 1) * delta_y) * cos(2 * M_PI * ((
                  float) j) * delta_x);
      float y = sin(M_PI * ((float) i + 1) * delta_y) * sin(2 * M_PI * ((
                  float) j) * delta_x);
      float z = cos(M_PI * ((float) i + 1) * delta_y);

      vbuff[ind].vertex[0] = radius * x;
      vbuff[ind].vertex[1] = radius * y;
      vbuff[ind].vertex[2] = radius * z;
      vbuff[ind].vertex[3] = 1.0f;

      vbuff[ind].normal[0] = x;
      vbuff[ind].normal[1] = y;
      vbuff[ind].normal[2] = z;

      vbuff[ind].texcoord[0] = ((float) j) * delta_x;
      vbuff[ind].texcoord[1] = 1.0f - ((float) i + 1) * delta_y;

      ind++;
    }
  }


  // inferior cap
  for (unsigned j = 0; j < sectors; j++) {
    vbuff[ind].vertex[0] = 0.0f;
    vbuff[ind].vertex[1] = 0.0f;
    vbuff[ind].vertex[2] = -radius;
    vbuff[ind].vertex[3] = 1.0f;

    vbuff[ind].normal[0] = 0.0f;
    vbuff[ind].normal[1] = 0.0f;
    vbuff[ind].normal[2] = -1.0f;

    vbuff[ind].texcoord[0] = delta_x / 2.0f + j * delta_x;
    vbuff[ind].texcoord[1] = 0.0f;

    ind++;
  }


  ind = 0;

  // INDICES

  // superior cap

  for (unsigned j = 0; j < sectors; j++) {
    ibuff[ind].v0 = j;
    ibuff[ind].v1 = sectors + j;
    ibuff[ind].v2 = sectors + j + 1;

    ind++;
  }


  // middle sphere
  for (unsigned i = 0; i < rings - 2; i++) {
    for (unsigned j = 0; j < sectors; j++) {
      ibuff[ind].v0 = j + sectors + i * (sectors + 1);
      ibuff[ind].v1 = j + sectors + (i + 1) * (sectors + 1);
      ibuff[ind].v2 = j + sectors + (i + 1) * (sectors + 1) + 1;

      ibuff[ind + 1].v0 = j + sectors + (i + 1) * (sectors + 1) + 1;
      ibuff[ind + 1].v1 = j + sectors + i * (sectors + 1) + 1;
      ibuff[ind + 1].v2 = j + sectors + i * (sectors + 1);

      ind = ind + 2;

    }
  }


  // inferior cap
  unsigned offset = sectors + (sectors + 1) * (rings - 1);

  for (unsigned j = 0; j < sectors; j++) {

    ibuff[ind].v0 = j + offset;
    ibuff[ind].v1 = j + offset - sectors;
    ibuff[ind].v2 = j + offset - (sectors + 1);

    ind++;
  }




  if (ms) {
    ms->setVertexBuffer(vbuff, vcount);
    ms->setIndexBuffer(ibuff, icount);
  }

  free(vbuff);
  free(ibuff);

}
