//#version 420
#version 410

// coordinates in world space

uniform mat4 view;
uniform mat4 model;

uniform struct Material {

  vec4 diffuseColor;
  vec4 specularColor;
  float shininess;
  sampler2D diffuseMap;

} material;


uniform struct Light {

   vec4 position;
   vec4 color; 
   float kc;
   float kl;
   float kq;
   float ambientCoef;

} light;

uniform vec3 gamma;


in vec4 fVertex;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 finalColor;




void main() {


  // Diffuse Color  
  
  vec4 texDiffuse = texture(material.diffuseMap, fTexCoord);

  float mdAlpha = texDiffuse.a;	        
       
  float dcAlpha = material.diffuseColor.a;

  vec4 albedoColor = (1.0 - mdAlpha) * material.diffuseColor + mdAlpha * texDiffuse;

  albedoColor.a = 1.0 - (1.0 - mdAlpha)*(1.0 - dcAlpha);


  vec4 pixelMod = albedoColor;  

  // Gamma correction

  finalColor = vec4(pow(pixelMod.rgb, vec3(1.0 / gamma)), albedoColor.a);

   
}