#version 330 core
out vec4 fragColor;


uniform sampler2D colorMap;
uniform float time;

in vec2 vtexCoord;

void main()
{
    vec2 C = vec2(0.272, 0.09);
    float r = 0.065;
    vec2 d = vec2(time, 0);
    vec2 Cx = fract(C+d);
    vec2 p = vtexCoord;
    if (distance(vtexCoord, Cx) < r) p = p - d;
    else if (distance(vtexCoord, C) < r) p = p + vec2(0.5,0);
    fragColor = texture(colorMap, p);
}
