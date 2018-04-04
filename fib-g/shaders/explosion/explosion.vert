#version 330 core


layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

uniform mat4 modelViewProjectionMatrixInverse;

out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

varying vec2 vtexCoord;


uniform float speed = 0.1;
uniform float time;

void main()
{
    vtexCoord = texCoord;
    frontColor = vec4(normalize(normalMatrix * normal).z);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

