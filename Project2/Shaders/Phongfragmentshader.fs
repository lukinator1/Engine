#version 330
in vec2 texcoordinates0;
in vec3 normal0;
in vec3 worldpos0;
struct Directionallight{
	vec3 color;
	vec3 direction;
	float intensity;
};
struct Attenuation{
	float linearterm;
	float quadraticterm;
};
struct Pointlight{
	vec3 color;
	float intensity;
	Attenuation attenuation;
	vec3 position;
};
uniform vec3 cameraposition;
uniform vec3 color;
uniform sampler2D sampler;
uniform vec3 ambientlight;
uniform float specularintensity;
uniform float specularexponent;
uniform Directionallight directionallight;  //change this to be an array
uniform Pointlight pointlights[5];	//may need to change depending on performance


vec4 caluclateLight(Directionallight dlight, vec3 normal)
{	
	vec4 diffuse = vec4(0, 0, 0, 0);
	vec4 specular = vec4(0, 0, 0, 0);

	float diffusefactor = dot(normal, -dlight.direction);  
	if (diffusefactor > 0) 
	{
	diffuse = vec4(dlight.color, 1.0) * dlight.intensity * diffusefactor;
	
	vec3 viewvector = normalize(cameraposition - worldpos0);
	vec3 reflection = normalize(reflect(dlight.direction, normal));
	float specfactor = dot(viewvector, reflection);

	if (specfactor > 0)
		{
	specfactor = pow(specfactor, specularexponent);
	specular = vec4(dlight.color, 1.0) * specularintensity * specfactor;
		}
	}

	return diffuse + specular;
}
vec4 calculateLight(Pointlight plight, vec3 direction, vec3 normal)
{	
	vec4 diffuse = vec4(0, 0, 0, 0);
	vec4 specular = vec4(0, 0, 0, 0);

	float diffusefactor = dot(normal, -direction);  
	if (diffusefactor > 0) 
	{
	diffuse = vec4(plight.color, 1.0) * plight.intensity * diffusefactor;
	
	vec3 viewvector = normalize(cameraposition - worldpos0);
	vec3 reflection = normalize(reflect(direction, normal));
	float specfactor = dot(viewvector, reflection);

	if (specfactor > 0)
		{
	specfactor = pow(specfactor, specularexponent);
	specular = vec4(plight.color, 1.0) * specularintensity * specfactor;
		}
	}

	return diffuse + specular;
}
float calculateAttenuation(Pointlight plight, float distance){	//change 0.0 to 1.0
	return 1.0/(0.0 + 
	plight.attenuation.linearterm * distance + 
	plight.attenuation.quadraticterm * distance * distance + .0001);
}

vec4 calculatePointLight (Pointlight point, vec3 normal){
	vec3 lightvector = worldpos0 - point.position;
	float lightdistance = length(lightvector);
	lightvector = normalize(lightvector);

	vec4 lighting = calculateLight(point, lightvector, normal);
	float attenuation = calculateAttenuation(point, lightdistance);
	return lighting * attenuation;
}

void main()
{
	vec4 totallight = vec4(ambientlight, 1.0);
	vec4 basecolor = vec4(color, 1);
	vec4 texture = texture2D(sampler, texcoordinates0.xy);
	vec3 normal =  normalize(normal0);

	totallight += caluclateLight(directionallight, normal);
	for (int i = 0; i < 4; i++){
	totallight += calculatePointLight(pointlights[i], normal);
	}

	gl_FragColor = texture * basecolor * totallight;
}