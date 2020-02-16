#version 330
layout (location = 0) in vec3 position;
out vec3 texturecoordinates0;
//uniform mat4 projectedtransform;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 skyboxmatrix;
//uniform bool infintelyscaling;

void main(){
	texturecoordinates0 = position;
	vec4 skyboxposition = skyboxmatrix * vec4(position, 1.0);
	gl_Position = skyboxposition.xyww;
}