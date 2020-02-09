#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoordinates;
layout (location = 2) in vec3 normal;
out vec2 texcoordinates0;
out vec3 normal0;
uniform float uniformFloat;
uniform mat4 transform;

void main ()
{
	texcoordinates0 = texcoordinates;
normal0 = normal;
	gl_Position = transform * vec4(position, 1.0);
}