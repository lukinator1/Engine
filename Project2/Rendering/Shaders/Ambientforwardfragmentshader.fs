#version 330
in vec2 texcoordinates0;
uniform vec3 ambientintensity;
uniform sampler2D sampler;
uniform vec3 color;
void main()
{
	vec4 basecolor = vec4(color, 1.0);
gl_FragColor = texture2D(sampler, texcoordinates0.xy) * basecolor * vec4(ambientintensity, 1.0);
}