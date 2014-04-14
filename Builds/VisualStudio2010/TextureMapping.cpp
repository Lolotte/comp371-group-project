#include <glew\include\GL\glew.h>
#include "TextureMapping.h"
#include "SOIL.h"


TextureMapping::TextureMapping(void)
{
}


TextureMapping::~TextureMapping(void)
{
}

void	TextureMapping::loadTexture(String const& textureFileName)
{
	int width, height;

	unsigned char *data = SOIL_load_image
	(
		textureFileName.toUTF8(),
		&width, &height, 0,
		SOIL_LOAD_RGBA
	);

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture ); 
	// set texture env
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
	// allows better quality texture, anisotropic filtering
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// texture repeats, not clamp
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	// generate the texture with read data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 480, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	int error = glGetError();
	delete data;
}

void TextureMapping::apply(int programID)
{
	glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);
	int texture_location = glGetUniformLocation(static_cast<GLuint>(programID), "texture");
	
	glUniform1i(texture_location, 0);
}

