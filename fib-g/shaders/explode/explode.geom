#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;



in vec3 P[];
in vec3 N[];

const float speed = 1.2;
uniform float time;

void main( void ) {
	vec3 n = vec3(0);
	for( int i = 0 ; i < 3 ; i++ ) {
		n += N[i];
	}
	n /= 3;
	for( int i = 0 ; i < 3 ; i++ ) {
		gfrontColor = vfrontColor[i];
		vec4 pos = vec4(P[i]+n*speed*mod(time, 2),1);
		pos = modelViewProjectionMatrix * pos;
		gl_Position = pos;
		EmitVertex();
	}
    EndPrimitive();
}
