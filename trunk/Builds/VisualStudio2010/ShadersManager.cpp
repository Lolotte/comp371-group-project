#include "ShadersManager.h"


ShadersManager::ShadersManager(OpenGLContext & contextOpenGL)
{
	_shaderProgram = new OpenGLShaderProgram(contextOpenGL);
}


ShadersManager::~ShadersManager(void)
{
}

void ShadersManager::addShader(String const& fragShaderName, String const& vertShaderName)
{
	File frag(File::getCurrentWorkingDirectory().getFullPathName() + "\\Shaders\\" + fragShaderName);
	File vert(File::getCurrentWorkingDirectory().getFullPathName() + "\\Shaders\\" + vertShaderName);

	String fragStr = frag.loadFileAsString();
	String vertStr = vert.loadFileAsString();

	_shaderProgram->addShader(fragStr, GL_FRAGMENT_SHADER);
	_shaderProgram->addShader(vertStr, GL_VERTEX_SHADER);
	_shaderProgram->link();
}

void ShadersManager::use()
{
	_shaderProgram->use();
}

void ShadersManager::release()
{
	_shaderProgram->release();
}