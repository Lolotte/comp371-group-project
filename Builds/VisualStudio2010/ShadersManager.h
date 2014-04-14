#pragma once
#include "JuceHeader.h"

class ShadersManager
{
public:
	ShadersManager(OpenGLContext & openGLcontext);
	~ShadersManager(void);

	void addShader(String const& fragShaderName, String const& vertShaderName);
	void use();
	void release();

private:
	OpenGLShaderProgram *_shaderProgram;
};

