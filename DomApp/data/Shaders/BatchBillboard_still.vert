uniform sampler2D teximage;
varying vec2 st;
varying vec3 stp;

void main()
{
	st = gl_MultiTexCoord0.xy;
	stp = gl_Vertex.xyz;
	
	
	gl_Position =  gl_ModelViewProjectionMatrix * gl_Vertex;

}