uniform sampler2D teximage;
attribute vec3 billboard_position;
uniform float angle_x;
uniform vec3 camera_position;


varying vec2 st;
varying vec3 stp;


void main()
{
	st = gl_MultiTexCoord0.xy;
	stp = gl_Vertex.xyz;

	mat4 RotationMatrix = mat4( cos( angle_x ), 0.0, sin( angle_x ), 0.0,
				    			0.0, 1.0, 0.0, 0.0,
				             	-sin( angle_x ), 0.0, cos( angle_x ), 0.0,
					     	   	0.0,           0.0, 0.0, 1.0 );

	mat4 TranslateMatrix = mat4(	1.0, 0.0, 0.0, 0.0,
									0.0, 1.0, 0.0, 0.0,
									0.0, 0.0, 1.0, 0.0,
									billboard_position.x, billboard_position.y,billboard_position.z, 1.0);

	
	//normal = gl_ModelViewMatrix*vec4(gl_Normal,0);
	gl_Position =  gl_ModelViewProjectionMatrix  * TranslateMatrix * RotationMatrix* gl_Vertex;
	//testcolor = TranslateMatrix*gl_Vertex;

}