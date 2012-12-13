uniform sampler2D teximage;

attribute vec3 position;
attribute float rotation;

uniform float angle_x;
uniform vec3 camera_position;
uniform int billboard;


varying vec2 st;
varying vec3 stp;


void main()
{
	st = gl_MultiTexCoord0.xy;
	stp = gl_Vertex.xyz;

	mat4 RotationMatrix = mat4( cos( rotation ), 0.0, sin( rotation ), 0.0,
				    			0.0, 1.0, 0.0, 0.0,
				             	-sin( rotation ), 0.0, cos( rotation ), 0.0,
					     	   	0.0,           0.0, 0.0, 1.0 );

	mat4 TranslateMatrix = mat4(	1.0, 0.0, 0.0, 0.0,
									0.0, 1.0, 0.0, 0.0,
									0.0, 0.0, 1.0, 0.0,
									position.x, position.y,position.z, 1.0);

	mat4 CameraMatrix = mat4( cos( angle_x ), 0.0, sin( angle_x ), 0.0,
					    			0.0, 1.0, 0.0, 0.0,
					             	-sin( angle_x ), 0.0, cos( angle_x ), 0.0,
						     	   	0.0,           0.0, 0.0, 1.0 );
	

	if(billboard == 0) {
		gl_Position =  gl_ModelViewProjectionMatrix  * TranslateMatrix *  RotationMatrix* gl_Vertex;
	} else {
		gl_Position =  gl_ModelViewProjectionMatrix  * TranslateMatrix * CameraMatrix * gl_Vertex;
	}

	
}