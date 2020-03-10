#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoordinates;
layout (location = 2) in vec3 normal;
out vec2 texcoordinates0;
out vec3 normal0;
out vec3 worldpos0;
uniform mat4 transform;
uniform mat4 projectedtransform;

void main ()
{
	gl_Position = projectedtransform * vec4(position, 1.0);
	texcoordinates0 = texcoordinates;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
	worldpos0 = (transform * vec4(position, 1.0)).xyz;
}