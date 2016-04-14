//#version 420
#version 410

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


in vec4 vVertex;
in vec3 vNormal;
in vec2 vTexCoord;

out vec2 fTexCoord;
out vec3 fNormal;
out vec4 fVertex;



void main() {

  fTexCoord = vTexCoord;
  fNormal = vNormal;
  fVertex = vVertex;

  gl_Position = projection * view * model  * vVertex;

}