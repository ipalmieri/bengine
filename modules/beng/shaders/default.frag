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
uniform float texctrl; 

in vec4 fVertex;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 finalColor;





void main() {

  // Parameters
  
  vec3 wNormal = normalize(vec3(transpose(inverse(view * model)) * vec4(fNormal, 0.0)));
  //vec3 wNormal = normalize(vec3(normal * vec4(fNormal, 0.0)));

  vec4 pixelPosition = view * model * fVertex;
  
  vec3 lightDirection = vec3(view * light.position - pixelPosition);
  
  float lightDistance = length(lightDirection);
  
  lightDirection = lightDirection / lightDistance; 
  
  vec3 eyeDirection = normalize(vec3(-pixelPosition));



  // Diffuse Color  
  
  vec4 texDiffuse = texture(material.diffuseMap, fTexCoord);

  float mdAlpha = texDiffuse.a * texctrl;	        

  float dcAlpha = material.diffuseColor.a;

  vec4 albedoColor = (1.0 - mdAlpha) * material.diffuseColor + mdAlpha * texDiffuse;

  albedoColor.a = 1.0 - (1.0 - mdAlpha)*(1.0 - dcAlpha);


  // Ambient Color 

  vec4 ambientColor = vec4(light.ambientCoef * albedoColor.xyz, albedoColor.w);

  
    
  // Attenuation

  float attenuation = 1.0 / (light.kc + light.kl * lightDistance + light.kq * lightDistance * lightDistance);

  float diffuseCoefficient = max(0.0, dot(wNormal, lightDirection));

  //attenuation = min(1.0, attenuation);  


  // Specular Color
  
  float specularCoefficient = 0.0;

  if(diffuseCoefficient > 0.0)
  {
    specularCoefficient =  max(0.0, dot(eyeDirection, reflect(-lightDirection, wNormal)));
    //specularCoefficient = max(0.0, dot(wNormal, normalize(lightDirection + eyeDirection)));
    	
    specularCoefficient = pow(specularCoefficient, material.shininess); 
  }	
  


  // Final Color Components

  vec4 ambientMod = ambientColor * light.color * attenuation;

  vec4 albedoMod = albedoColor * attenuation * diffuseCoefficient * light.color; 
  
  vec4 specularMod = specularCoefficient * light.color * material.specularColor * attenuation;
  

  vec4 pixelMod = ambientMod + albedoMod + specularMod;

  pixelMod = min(pixelMod, vec4(1.0));

  

  // Gamma correction

  finalColor = vec4(pow(pixelMod.rgb, vec3(1.0 / gamma)), albedoColor.a);

 
  //finalColor = vec4(pixelMod.rgb, albedoColor.a);
  //finalColor = vec4(fNormal, 1.0);
  //finalColor = material.diffuseColor;
  //finalColor = vec4(0.5, 0.5, 1.0, 1.0);

  //finalColor = material.diffuseColor;

}