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
	GLuint	getProgramID() const;
	bool isActive() const;

private:
	bool _isActive;
	OpenGLContext &_openGLcontext;
	OpenGLShaderProgram *_shaderProgram;
};

