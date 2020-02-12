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
	float range;
};
struct Spotlight{
	vec3 color;
	vec3 position;
	vec3 direction;
	float intensity;
	Attenuation attenuation;
	float range;
	float cutoff;
};
uniform vec3 cameraposition;
uniform vec3 color;
uniform sampler2D sampler;
uniform vec3 ambientlight;
uniform float specularintensity;
uniform float specularexponent;
uniform Directionallight directionallight;  //change this to be an array
uniform Pointlight pointlights[5];	//may need to change depending on performance
uniform Spotlight spotlights[5];


float calculateAttenuation(Pointlight plight, float distance){	//change 0.0 to 1.0
	return 1.0/(0.0 + 
	plight.attenuation.linearterm * distance + 
	plight.attenuation.quadraticterm * distance * distance + .0001);
}

float calculateAttenuation(Spotlight slight, float distance){	//change 0.0 to 1.0
	return 1.0/(0.0 + 
	slight.attenuation.linearterm * distance + 
	slight.attenuation.quadraticterm * distance * distance + .0001);
}




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
vec4 calculateLight(Spotlight slight, vec3 direction, vec3 normal)
{	
	vec4 diffuse = vec4(0, 0, 0, 0);
	vec4 specular = vec4(0, 0, 0, 0);

	float diffusefactor = dot(normal, -direction);  
	if (diffusefactor > 0) 
	{
	diffuse = vec4(slight.color, 1.0) * slight.intensity * diffusefactor;
	
	vec3 viewvector = normalize(cameraposition - worldpos0);
	vec3 reflection = normalize(reflect(direction, normal));
	float specfactor = dot(viewvector, reflection);

	if (specfactor > 0)
		{
	specfactor = pow(specfactor, specularexponent);
	specular = vec4(slight.color, 1.0) * specularintensity * specfactor;
		}
	}

	return diffuse + specular;
}






vec4 calculateDirectionalLight(Directionallight directional, vec3 normal){
	return calculateLight(directional, normal);
}
vec4 calculatePointLight (Pointlight point, vec3 normal){
	vec3 lightvector = worldpos0 - point.position;
	float lightdistance = length(lightvector);
	if (lightdistance > point.range){
	return vec4(0.0, 0.0, 0.0, 0.0);
	}
	lightvector = normalize(lightvector);

	vec4 lighting = calculateLight(point, lightvector, normal);
	float attenuation = calculateAttenuation(point, lightdistance);
	return lighting * attenuation;
}
vec4 calculateSpotLight (Spotlight spot, vec3 normal){
	vec3 lightvector = worldpos0 - spot.position;
	vec3 lightdirection = normalize(lightvector);
	float spotfactor = dot(lightdirection, spot.direction);
	vec4 color = vec4(0, 0, 0, 0);
	if (spotfactor > spot.cutoff){

	float lightdistance = length(lightvector);
	if (lightdistance > spot.range){
	return vec4(0.0, 0.0, 0.0, 0.0);
	}

	vec4 lighting = calculateLight(spot, lightdirection, normal);
	float attenuation = calculateAttenuation(spot, lightdistance);

	color = (lighting * attenuation) * (1.0 - (1.0 - spotfactor)/(1.0 - spot.cutoff)); 	//change equation for bettter look?
	}
	return color;
}






void main()
{
	vec4 totallight = vec4(ambientlight, 1.0);
	vec4 basecolor = vec4(color, 1);
	vec4 texture = texture2D(sampler, texcoordinates0.xy);
	vec3 normal =  normalize(normal0);

	totallight += calculateDirectionalLight(directionallight, normal);
	for (int i = 0; i < 5; i++){
	if (pointlights[i].intensity != 0.0){
	totallight += calculatePointLight(pointlights[i], normal);
		}
	if (spotlights[i].intensity != 0.0){
	totallight += calculateSpotLight(spotlights[i], normal);
		}
	}

	gl_FragColor = texture * basecolor * totallight;
}