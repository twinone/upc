#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void print(float x, float y) {
	for( int i = 0; i < 3 ; i++ ) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		gl_Position /= gl_Position.w;
		gl_Position.x += x;
		gl_Position.y += y;
		EmitVertex();
	}
	EndPrimitive();
}

void main( void ) {
	print(-0.5, -0.5);
	print(-0.5,  0.5);
	print( 0.5, -0.5);
	print( 0.5,  0.5);
}
