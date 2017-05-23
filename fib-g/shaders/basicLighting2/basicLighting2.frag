#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in float nz;

void main()
{
    fragColor = frontColor * nz;
}
