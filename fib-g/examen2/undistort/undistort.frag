#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;


bool ok(float x) { return x >= 0 && x <= 1; }

void main()
{
    vec2 Q = (vtexCoord)*2 - vec2(1);

    float r = length(Q);
    float rp = (r + 0.22*pow(r,3)+0.24*pow(r,5));
    vec2 Qp = rp * normalize(Q);
    vec2 Qf = (Qp+vec2(1))/2;

    if (ok(Qf.s) && ok(Qf.t))
        fragColor = texture(colorMap, Qf);
    else
	fragColor = vec4(0,0,0,1);
}
