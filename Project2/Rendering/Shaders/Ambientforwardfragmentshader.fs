#version 330
in vec2 texcoordinates0;
uniform vec3 ambientintensity;
uniform sampler2D sampler;
void main()
{
	gl_FragColor = texture2D(sampler, texcoordinates0.xy) * vec4(ambientintensity, 1);
}