#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform mat3 normalMatrix;


in vec3 N[];
uniform float disp = 0.05;

void main( void )
{
	vec3 bari = vec3(0);
	vec3 norm = vec3(0);
	for (int i = 0; i < 3; i++) {
		bari += gl_in[i].gl_Position.xyz;
		norm += N[i];
	}
	norm/=3;
	bari/=3;

	vec3 V = bari+norm*disp;

	// original triangle
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
		EmitVertex();

	}
	EndPrimitive();

	// spike triangle
	for( int i = 0 ; i < 3 ; i++ )
	{
		int j = (i+1)%3;


		gfrontColor = vfrontColor[j];
		gl_Position = modelViewProjectionMatrix*gl_in[j].gl_Position;
		EmitVertex();

		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
		EmitVertex();

		
		gfrontColor = vec4(1,1,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(V,1);
		EmitVertex();
		EndPrimitive();
	}

}
