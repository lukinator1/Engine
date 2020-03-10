#version 330
in vec2 texcoordinates0;
in vec3 normal0;
in vec3 worldpos0;
struct Attenuation{
	float linearterm;
	float quadraticterm;
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
uniform float specularintensity;
uniform float specularexponent;
uniform Spotlight spotlight;


float calculateAttenuation(Spotlight slight, float distance){	//change 0.0 to 1.0
	return 1.0/(0.001 + 
	slight.attenuation.linearterm * distance + 
	slight.attenuation.quadraticterm * distance * distance);
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
	vec4 totallight = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 basecolor = vec4(color, 1);
	vec4 texture = texture2D(sampler, texcoordinates0.xy);
	vec3 normal =  normalize(normal0);

	totallight += calculateSpotLight(spotlight, normal);

	gl_FragColor = texture * basecolor * totallight;
}