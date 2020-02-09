#version 330
in vec2 texcoordinates0;
in vec3 normal0;
struct Directionallight{
	vec3 color;
	vec3 direction;
	float intensity;
};
uniform vec3 color;
uniform sampler2D sampler;
uniform vec3 ambientlight;
uniform Directionallight directionallight;

vec4 caluclateDirectionalLight(Directionallight dlight, vec3 normal)
{
	float diffusefactor = dot(normal, -dlight.direction);
	if (diffusefactor > 0) {
	vec4 diffuse = vec4(dlight.color, 1.0) * dlight.intensity * diffusefactor;
	return diffuse;
	}
	else{ 
		return vec4(0.0, 0.0, 0.0, 0.0);
	}
}

void main()
{
	vec4 totallight = vec4(ambientlight, 1.0);
	vec4 basecolor = vec4(color, 1);
	vec4 texture = texture2D(sampler, texcoordinates0.xy);
	vec3 normal =  normalize(normal0);

	totallight += caluclateDirectionalLight(directionallight, normal);

	if (texture != vec4(0.0, 0.0, 0.0, 0.0)){
	gl_FragColor = texture * basecolor * totallight;
		}
	else{
	gl_FragColor = basecolor * totallight;
		}
}