#include "Skybox.h"
Skybox::Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) : skyboxshader("Skybox")
{
	/*Vertex skyboxvertices[] = {       
		Vertex(vector3(-1.0f,  1.0f, -1.0f)),
		Vertex(vector3(-1.0f, -1.0f, -1.0f)),
		Vertex(vector3(1.0f, -1.0f, -1.0f)),
		Vertex(vector3(1.0f, -1.0f, -1.0f)),
		Vertex(vector3(1.0f,  1.0f, -1.0f)),
		Vertex(vector3(-1.0f,  1.0f, -1.0f)),

		Vertex(vector3(-1.0f, -1.0f,  1.0f)),
		Vertex(vector3(-1.0f, -1.0f, -1.0f)),
		Vertex(vector3(-1.0f,  1.0f, -1.0f)),
		Vertex(vector3(-1.0f,  1.0f, -1.0f)),
		Vertex(vector3(-1.0f,  1.0f,  1.0f)),
		Vertex(vector3(-1.0f, -1.0f,  1.0f)),

		Vertex(vector3(1.0f, -1.0f, -1.0f)),
		Vertex(vector3(1.0f, -1.0f,  1.0f)),
		Vertex(vector3(1.0f,  1.0f,  1.0f)),
		Vertex(vector3(1.0f,  1.0f,  1.0f)),
		Vertex(vector3(1.0f,  1.0f, -1.0f)),
		Vertex(vector3(1.0f, -1.0f, -1.0f)),

		Vertex(vector3(-1.0f, -1.0f,  1.0f)),
		Vertex(vector3(-1.0f,  1.0f,  1.0f)),
		Vertex(vector3(1.0f,  1.0f,  1.0f)),
		Vertex(vector3(1.0f,  1.0f,  1.0f)),
		Vertex(vector3(1.0f, -1.0f,  1.0f)),
		Vertex(vector3(-1.0f, -1.0f,  1.0f)),

		Vertex(vector3(-1.0f,  1.0f, -1.0f)),
		Vertex(vector3(1.0f,  1.0f, -1.0f)),
		Vertex(vector3(1.0f,  1.0f,  1.0f)),
		Vertex(vector3(1.0f,  1.0f,  1.0f)),
		Vertex(vector3(-1.0f,  1.0f,  1.0f)),
		Vertex(vector3(-1.0f,  1.0f, -1.0f)),

		Vertex(vector3(-1.0f, -1.0f, -1.0f)),
		Vertex(vector3(-1.0f, -1.0f,  1.0f)),
		Vertex(vector3(1.0f, -1.0f, -1.0f)),
		Vertex(vector3(1.0f, -1.0f, -1.0f)),
		Vertex(vector3(-1.0f, -1.0f,  1.0f)),
		Vertex(vector3(1.0f, -1.0f,  1.0f))
	};*/
	/*float skyboxvertices[] = {
		// positions          
		-1.0f * size,  1.0f * size, -1.0f * size,
		-1.0f * size, -1.0f * size, -1.0f * size,
		 1.0f * size, -1.0f * size, -1.0f * size,
		 1.0f * size, -1.0f * size, -1.0f * size,
		 1.0f * size,  1.0f * size, -1.0f * size,
		-1.0f * size,  1.0f * size, -1.0f * size,

		-1.0f * size, -1.0f * size,  1.0f * size,
		-1.0f * size, -1.0f * size, -1.0f * size,
		-1.0f * size,  1.0f * size, -1.0f * size,
		-1.0f * size,  1.0f * size, -1.0f * size,
		-1.0f * size,  1.0f * size,  1.0f * size,
		-1.0f * size, -1.0f * size,  1.0f * size,

		 1.0f * size, -1.0f * size -1.0f * size,
		 1.0f * size, -1.0f * size,  1.0f * size,
		 1.0f * size,  1.0f * size,  1.0f * size,
		 1.0f * size,  1.0f * size,  1.0f * size,
		 1.0f * size,  1.0f * size, -1.0f * size,
		 1.0f * size, -1.0f * size, -1.0f * size,

		-1.0f * size, -1.0f * size,  1.0f * size,
		-1.0f * size,  1.0f * size,  1.0f * size,
		 1.0f * size,  1.0f * size,  1.0f * size,
		 1.0f * size,  1.0f * size,  1.0f * size,
		 1.0f * size, -1.0f * size,  1.0f * size,
		-1.0f * size, -1.0f * size,  1.0f * size,

		-1.0f * size,  1.0f * size, -1.0f * size,
		 1.0f * size,  1.0f * size, -1.0f * size,
		 1.0f * size,  1.0f * size,  1.0f * size,
		 1.0f * size,  1.0f * size,  1.0f * size,
		-1.0f * size,  1.0f * size,  1.0f * size,
		-1.0f * size,  1.0f * size, -1.0f * size,

		-1.0f * size, -1.0f * size, -1.0f * size,
		-1.0f * size, -1.0f * size,  1.0f * size,
		 1.0f * size, -1.0f * size, -1.0f * size,
		 1.0f * size, -1.0f * size, -1.0f * size,
		-1.0f * size, -1.0f * size,  1.0f * size,
		 1.0f * size, -1.0f * size,  1.0f * size
	};*/
	float skyboxvertices[] = {         
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	/*for (int i = 0; i < 108; i++) {
		skyboxvertices[i] *= size;
	}*/
	skyboxbox.makeSkyboxMesh(skyboxvertices, 36);
	skyboxtexture.loadCubeMap(right, left, top, bottom, front, back);
}
void Skybox::useSkybox()
{
	glDepthFunc(GL_LEQUAL);
	skyboxshader.useShader();
	/*Materials mat("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);
	skyboxshader.updateUniforms(t.newUnprojectedMatrix(), t.newTransformationMatrix(), t.position, mat);*/
	skyboxshader.setUniform("skyboxmatrix", t.newSkyboxMatrix());
	/*skyboxshader.setUniform("projectedtransform", t.newTransformationMatrix());
	skyboxshader.setUniform("view", t.newViewMatrix());
	skyboxshader.setUniform("projection", t.newProjectionMatrix());*/
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxtexture.textureid);
	skyboxbox.drawNoIndicesMesh();
	glDepthFunc(GL_LESS);
}
Skybox::~Skybox()
{
}
