#pragma once

#include "JuceHeader.h"


class TextureMapping
{
public:
	TextureMapping(void);
	~TextureMapping(void);

	void	apply(int programID);
	void	loadTexture(String const& textureFileName);

private:
	GLuint texture;
};

