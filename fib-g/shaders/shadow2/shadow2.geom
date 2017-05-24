#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;


void emit(vec3 C, float x, float z) {
	gl_Position = modelViewProjectionMatrix*vec4(C.x+x, boundingBoxMin.y-0.1, C.z+z, 1);
	EmitVertex();
}
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


	if (gl_PrimitiveIDIn != 0) return;

	vec3 C = (boundingBoxMax-boundingBoxMin)/2+boundingBoxMin;
	float R = length(boundingBoxMax-boundingBoxMin)/2;

	gfrontColor = vec4(0,1,1,1); // cyan
	

	emit(C, -R, -R); emit(C, -R, R); emit(C, R, -R); EndPrimitive();
	emit(C, -R, R); emit(C, R, -R); emit(C, R, R); EndPrimitive();
	
}












