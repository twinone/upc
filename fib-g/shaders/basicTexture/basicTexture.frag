#version 330 core

in vec4 frontColor;
out vec4 fragColor;

varying vec2 vtexCoord;
uniform sampler2D colorMap; // map 0

void main()
{
    fragColor = frontColor * texture(colorMap, vtexCoord);
}
