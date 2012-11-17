uniform sampler2D teximage;
varying vec2 st; // 2D texcoords (from OpenGL texcoords)
varying vec3 stp; // 3D texcoords (from vertex xyz position)

void main()
{
  	vec4 rgba = texture2D(teximage, st); // RGB image
	if(rgba.a < 0.5) {
		discard;
	}
	if(gl_FragDepth > 3.0) {
		discard;
	}
	gl_FragColor = vec4( rgba);
}