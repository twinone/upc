#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform vec3 boundingBoxMin;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	
float minY = boundingBoxMin.y;
for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0,0,0,1);
		vec4 p = modelViewProjectionMatrixInverse*gl_in[i].gl_Position;
p.y = minY;
		gl_Position = modelViewProjectionMatrix*p;
		EmitVertex();
	}
    EndPrimitive();
}
