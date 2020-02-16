#version 330
in vec3 texturecoordinates0;
uniform samplerCube skybox;

void main(){
	gl_FragColor = texture(skybox, texturecoordinates0);
}