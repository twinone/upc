#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;



in vec3 P[];
in vec3 N[];

const float speed = 1.2;
const float angSpeed = 8.0;
uniform float time;

void main( void ) {
	vec3 n = vec3(0);
	vec3 bari = vec3(0);
	for( int i = 0 ; i < 3 ; i++ ) {
		n += N[i];
		bari += P[i];
	}
	bari /= 3;
	n /= 3;
	float a = time*angSpeed;
	mat3 rot = mat3(vec3(cos(a), sin(a), 0),
			vec3(-sin(a), cos(a), 0),
			vec3(0, 0, 1));
	

	for( int i = 0 ; i < 3 ; i++ ) {
		gfrontColor = vfrontColor[i];
		
		vec3 pos = P[i] - bari;
		pos = rot * pos;
		pos += bari+n*speed*mod(time,2);
		gl_Position = modelViewProjectionMatrix * vec4(pos,1);

		EmitVertex();
	}
    EndPrimitive();
}
