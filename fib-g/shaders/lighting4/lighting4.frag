#version 330 core

in vec4 frontColor;
out vec4 fragColor;


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




in vec3 P;
in vec3 N;




void main()
{
    vec3 V = normalize(-P);

    vec3 L = normalize(lightPosition.xyz - P);
    vec3 R = normalize(2*dot(N,L) * N - L);

    float NL = max(0, dot(N, L));
    float RV = max(0, dot(R, V));




    vec3 A = vec3(matAmbient * lightAmbient);
    vec3 D = vec3(matDiffuse * lightDiffuse);
    vec3 S = vec3(matSpecular * lightSpecular);
    
    vec3 KI = A+ D*NL + S*pow(RV, matShininess);

    fragColor = vec4(KI, 1.0);

}
