#version 330 core

in vec4 frontColor;
out vec4 fragColor;

varying vec2 vtexCoord;
uniform sampler2D explosion; // map 0

uniform float time;

void main()
{


    float frame = floor(time * 30);
    vec2 v = vtexCoord;
    float ds = frame;
    float dt = -floor(frame / 8);

    // go to 0,0
    v.s = v.s + 0;
    v.t = v.t + 5;

    // move to the coords
    v.s = v.s + ds;
    v.t = v.t + dt;

    // scale for the tile
    v.s = v.s / 8;
    v.t = v.t / 6;
    vec4 color = texture(explosion, v);
    color = color * color.a;
    fragColor = frontColor * color;
}
