#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;


void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vec4 p = modelViewProjectionMatrix * vec4(vertex, 1.0);
    float s = 0.5 * abs(sin(time));

    p.x = p.x * s;
    p.y = p.y * s;
    gl_Position = p;
}
