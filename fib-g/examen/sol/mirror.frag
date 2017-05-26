#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colorMap;
uniform float time;


void main()
{
    vec2 v = vtexCoord;
    bool tm = time <= 0.5;
    bool px = v.s < 0.5;
    if (tm && px || !tm && !px)
	    v.s = 1 - v.s;
    
    fragColor = texture(colorMap, v);
}
