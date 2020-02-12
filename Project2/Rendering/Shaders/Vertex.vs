#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoordinates;
out vec2 texcoordinates0;
uniform float uniformFloat;
uniform mat4 transform;

void main ()
{
	texcoordinates0 = texcoordinates;
	gl_Position = transform * vec4(position, 1.0);
}