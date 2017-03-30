
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

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vec3 V = vec3(0,0,1);
    vec3 P = (modelViewMatrix * vec4(vertex.xyz, 1)).xyz;
    vec3 L = normalize(lightPosition.xyz - P);

    vec3 H = normalize(V + L);

    float NL = max(0, dot(N, L));
    float NH = max(0, dot(N, H));

    vec3 A = vec3(matAmbient * lightAmbient);
    vec3 D = vec3(matDiffuse * lightDiffuse);
    vec3 S = vec3(matSpecular * lightSpecular);
    
    vec3 KI = A+ D*NL + S*pow(NH, matShininess);


    frontColor = vec4(KI,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}




























