#include "ShadersManager.h"


ShadersManager::ShadersManager(OpenGLContext & contextOpenGL)
	: _isActive(false), _openGLcontext(contextOpenGL)
{
	_shaderProgram = new OpenGLShaderProgram(contextOpenGL);
}


ShadersManager::~ShadersManager(void)
{
	delete _shaderProgram;
}

void ShadersManager::addShader(String const& fragShaderName, String const& vertShaderName)
{
	_isActive = true;

	File frag(File::getCurrentWorkingDirectory().getFullPathName() + "\\Shaders\\" + fragShaderName);
	File vert(File::getCurrentWorkingDirectory().getFullPathName() + "\\Shaders\\" + vertShaderName);

	String fragStr = frag.loadFileAsString();
	String vertStr = vert.loadFileAsString();

	_shaderProgram->addShader(fragStr, GL_FRAGMENT_SHADER);
	_shaderProgram->addShader(vertStr, GL_VERTEX_SHADER);
	if (_openGLcontext.isActive())
		_shaderProgram->link();
}

GLuint ShadersManager::getProgramID() const {return _shaderProgram->getProgramID();}

void ShadersManager::use()
{
	_shaderProgram->use();
}

void ShadersManager::release()
{
	_isActive = false;
	_shaderProgram->release();
}

bool ShadersManager::isActive() const {return _isActive;}