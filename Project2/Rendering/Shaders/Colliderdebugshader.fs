#version 330
in vec2 texcoordinates0;
uniform sampler2D sampler;
uniform vec3 color;
uniform int textured;
void main()
{
	vec4 basecolor = vec4(color, 0.0);
	if (textured == 1){
gl_FragColor = texture2D(sampler, texcoordinates0.xy) * basecolor;
}
	if (textured == 0){
gl_FragColor = basecolor;
}
}