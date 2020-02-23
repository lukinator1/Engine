#include "Rendertext.h"
Rendertext::Rendertext() : textshader("textshader")
{
	if (FT_Init_FreeType(&ft)) {
		engineLog(__FILE__, __LINE__, "FreeType text renderer failed to load.", 3, 2, false);
	}
	textshader.useShader();
	textshader.setUniform("textmatrix", t.newTextMatrix());
}
void Rendertext::loadText() {
	/*FT_Face face;
	if (FT_New_Face(ft, "C:/Users/lukinator1/Desktop/engine/The Super Suspension System/Project2/Project2/Rendering/Textfonts/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			vector2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows),
			vector2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/

	FT_Face face;
	if (FT_New_Face(ft, "Rendering/Textfonts/arial.ttf", 0, &face)) {
		engineLog(__FILE__, __LINE__, "Text font failed to load.", 2, 2, false);
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte i = 0; i < 128; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			engineLog(__FILE__, __LINE__, "A glyph failed to load.", 1, 2, false);
		}

		GLuint texttexture;
		glGenTextures(1, &texttexture);
		glBindTexture(GL_TEXTURE_2D, texttexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
			GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character newchar{texttexture, vector2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows), vector2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top), face->glyph->advance.x};
		characters.insert(std::pair<GLchar, Character>(i, newchar));
	}	
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Rendertext::renderText(std::string text, float _x, float _y, vector3 color, float scale) {
	/*glCullFace(GL_BACK);*/ 
	glFrontFace(GL_CCW);
	textshader.useShader();
	textshader.setUniform("textcolor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);
	std::string::const_iterator i;
	for (i = text.begin(); i != text.end(); i++) {
		Character currentchar = characters[*i];
		GLfloat xpos = _x + currentchar.bearing.x * scale;
		GLfloat ypos = _y - (currentchar.size.y - currentchar.bearing.y) * scale;

		GLfloat w = currentchar.size.x * scale;
		GLfloat h = currentchar.size.y * scale;

		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h, 0.0, 0.0 },
			{ xpos,     ypos,     0.0, 1.0 },
			{ xpos + w, ypos,     1.0, 1.0 },
			{ xpos,     ypos + h,  0.0, 0.0 },
			{ xpos + w, ypos,      1.0, 1.0 },
			{ xpos + w, ypos + h,  1.0, 0.0 }
		};
		/*GLfloat xpos = _x + currentchar.bearing.x * scale;
		GLfloat ypos = _y - (currentchar.size.y - currentchar.bearing.y) * scale;
		GLfloat w = currentchar.size.x * scale;
		GLfloat h = currentchar.size.y * scale;
		GLfloat vertices[6][4] = {
		{ xpos, ypos + h, 0.0,  0.0},
		{ xpos, ypos,     0.0,  1.0},
		{ xpos + w,   ypos,   1.0, 1.0},
		{ xpos,   ypos + h,  0.0, 0.0},
		{ xpos + w, ypos,  1.0, 1.0},
		{ xpos + w, ypos + h, 1.0, 0.0}
		};*/
		glBindTexture(GL_TEXTURE_2D, currentchar.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		_x += (currentchar.stride >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFrontFace(GL_CW);
}
Rendertext::~Rendertext()
{
	FT_Done_FreeType(ft);
}
