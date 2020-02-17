#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H
#include "Texture.h"
#include "Transforming.h"
#include "../Window.h"
#include "../Logger.h"
#include "Shader.h"
#include "../Mathlibrary/vector2.h"
#include <map>
class Rendertext : public Logger
{
public:
	FT_Library ft;
	Transforming t;
	struct Character {
		/*Character(GLuint &textID, unsigned int width, unsigned int rows, FT_Int left, FT_Int top, FT_Pos &_stride) {
			textureID = textID;
			size.x = width;
			size.y = rows;
			bearing.x = left;
			bearing.y = top;
			stride = _stride;
		}*/
			/*Character();*/
		GLuint textureID;
		vector2 size;
		vector2 bearing;
		GLuint stride;
	};
	Shader textshader;
	GLuint vao, vbo;
	std::map<GLchar, Character> characters;
	/*SDL_Renderer* sdlrenderer;
	SDL_Texture* sdltexture;
	Texture texttexture*/
	void setSDLRendererToWindow(Window &window);
	void loadText();
	void renderText(std::string text, float x, float y, vector3 color, float scale);
	Rendertext();
	~Rendertext();
};

