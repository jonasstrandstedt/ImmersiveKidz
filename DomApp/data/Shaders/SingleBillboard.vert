uniform sampler2D teximage;
varying vec2 st;
varying vec3 stp;

uniform float angle_x;
uniform vec3 camera_pos;

void main()
{
	st = gl_MultiTexCoord0.xy;
	stp = gl_Vertex.xyz;
	
	mat4 RotationMatrix = mat4( cos( angle_x ), 0.0, sin( angle_x ), 0.0,
				    			0.0, 1.0, 0.0, 0.0,
				             	-sin( angle_x ), 0.0, cos( angle_x ), 0.0,
					     	   	0.0,           0.0, 0.0, 1.0 );
	
	gl_Position =  gl_ModelViewProjectionMatrix * RotationMatrix * gl_Vertex;

}