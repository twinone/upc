#version 330 core


layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

uniform mat4 modelMatrixInverse;
uniform mat4 viewMatrixInverse;
uniform mat4 projectionMatrixInverse;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelViewProjectionMatrixInverse;


uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space
uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess



out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float n = 4;

void main()
{

    vec3 F = (modelViewMatrixInverse * lightPosition).xyz;
    float d = distance(F, vertex);
    float w = clamp(1/pow(d,n), 0, 1);
 

    vec3 VV = (1.0-w)*vertex + w*F;

    vec3 N = normalize(normalMatrix * normal);

    frontColor = vec4(normalize(normalMatrix * normal).z);
    gl_Position = modelViewProjectionMatrix * vec4(VV, 1.0);
}

