#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 textcoordinates0;
uniform mat4 textmatrix;

void main()
{
	gl_Position = textmatrix * vec4(vertex.xy, 0.0, 1.0);
	textcoordinates0 = vertex.zw;
}