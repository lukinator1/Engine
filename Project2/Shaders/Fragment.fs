#version 330
in vec4 color;
out vec4 fragcolor;

void main()
{
	fragcolor = vec4(0.0f, 1.0f, 1.0f, 1.0f);
	fragcolor = color;
}