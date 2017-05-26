#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 3) in vec2 texCoord;


out vec2 vtexCoord;
out vec4 vfrontColor;

uniform mat4 modelViewProjectionMatrix;


void main()
{

    vtexCoord = texCoord;

  
    // in object space, scale
    vec3 vv = vertex;
    vv.x /= 2;
    gl_Position = modelViewProjectionMatrix * vec4(vv, 1.0);
}
