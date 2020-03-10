#version 330
in vec2 texcoordinates0;
in vec3 normal0;
in vec3 worldpos0;
struct Directionallight{
	vec3 color;
	vec3 direction;
	float intensity;
};
uniform vec3 cameraposition;
uniform vec3 color;
uniform sampler2D sampler;
uniform float specularintensity;
uniform float specularexponent;
uniform Directionallight directionallight;  //change this to be an array

vec4 calculateLight(Directionallight dlight, vec3 normal)
{	
	vec4 diffuse = vec4(0, 0, 0, 0);
	vec4 specular = vec4(0, 0, 0, 0);

	float diffusefactor = dot(normal, dlight.direction);  
	if (diffusefactor > 0) 
	{
	diffuse = vec4(dlight.color, 1.0) * dlight.intensity * diffusefactor;
	
	vec3 viewvector = normalize(cameraposition - worldpos0);
	vec3 reflection = normalize(reflect(-dlight.direction, normal));
	float specfactor = dot(viewvector, reflection);

	if (specfactor > 0)
		{
	specfactor = pow(specfactor, specularexponent);
	specular = vec4(dlight.color, 1.0) * specularintensity * specfactor;
		}
	}

	return diffuse + specular;
}

vec4 calculateDirectionalLight(Directionallight directional, vec3 normal){
	return calculateLight(directional, normal);
}

void main()
{
	vec4 totallight = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 basecolor = vec4(color, 1);

	vec4 texture = texture2D(sampler, texcoordinates0.xy);
	vec3 normal =  normalize(normal0);
	totallight += calculateDirectionalLight(directionallight, normal);
	
	gl_FragColor = texture * basecolor * totallight;
}