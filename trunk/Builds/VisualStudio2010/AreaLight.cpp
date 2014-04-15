#include "JuceHeader.h"
#include "AreaLight.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\glut.h>


AreaLight::AreaLight(void)
{
	this->initializeKeys();
}


AreaLight::~AreaLight(void)
{
}

void	AreaLight::initializeKeys()
{
	_keyEvents[49] = &AreaLight::enableLight;
	_keyEvents[50] = &AreaLight::enableLight;
	_keyEvents[51] = &AreaLight::enableLight;
	_keyEvents[52] = &AreaLight::enableLight;
	_keyEvents[53] = &AreaLight::enableLight;
	_keyEvents[54] = &AreaLight::enableLight;
	_keyEvents[55] = &AreaLight::enableLight;
	_keyEvents[56] = &AreaLight::enableLight;
	_keyEvents[79] = &AreaLight::disableAllLights;
	_keyEvents[80] = &AreaLight::enableAllLights;
}

void	AreaLight::initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

	glEnable(GL_NORMALIZE);	

	_lightsStatus[GL_LIGHT0] = true;
	_lightsStatus[GL_LIGHT1] = true;
	_lightsStatus[GL_LIGHT2] = true;
	_lightsStatus[GL_LIGHT3] = true;
	_lightsStatus[GL_LIGHT4] = true;
	_lightsStatus[GL_LIGHT5] = true;
	_lightsStatus[GL_LIGHT6] = true;
	_lightsStatus[GL_LIGHT7] = true;
}

void	AreaLight::render()
{
	std::map<GLenum, bool>::iterator it = _lightsStatus.begin();

	for (; it != _lightsStatus.end(); ++it)
		if (it->second)
			glEnable(it->first);
		else
			glDisable(it->first);

	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {10.0f, 10.0f, 10.0f, 1.0f}; //Positioned at (10, 10, 10)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	GLfloat lightColor1[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos1[] = {-10.0f, 10.0f, 10.0f, 1.0f}; //Positioned at (-10, 10, 10)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	GLfloat lightColor2[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos2[] = {10.0f, 10.0f, -10.0f, 1.0f}; //Positioned at (10, 10, -10)
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

	GLfloat lightColor3[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos3[] = {-10.0f, 10.0f, -10.0f, 1.0f}; //Positioned at (-10, 10, -10)
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor3);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);

	GLfloat lightColor4[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos4[] = {10.0f, -10.0f, 10.0f, 1.0f}; //Positioned at (10, -10, 10)
	glLightfv(GL_LIGHT4, GL_DIFFUSE, lightColor4);
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);

	GLfloat lightColor5[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos5[] = {-10.0f, -10.0f, 10.0f, 1.0f}; //Positioned at (-10, -10, 10)
	glLightfv(GL_LIGHT5, GL_DIFFUSE, lightColor5);
	glLightfv(GL_LIGHT5, GL_POSITION, lightPos5);

	GLfloat lightColor6[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos6[] = {10.0f, -10.0f, -10.0f, 1.0f}; //Positioned at (10, -10, -10)
	glLightfv(GL_LIGHT6, GL_DIFFUSE, lightColor6);
	glLightfv(GL_LIGHT6, GL_POSITION, lightPos6);

	GLfloat lightColor7[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos7[] = {-10.0f, -10.0f, -10.0f, 1.0f}; //Positioned at (10, -10, -10)
	glLightfv(GL_LIGHT7, GL_DIFFUSE, lightColor7);
	glLightfv(GL_LIGHT7, GL_POSITION, lightPos7);
}

void	AreaLight::enableAllLights(int keyCode)
{
	_lightsStatus[GL_LIGHT0] = true;
	_lightsStatus[GL_LIGHT1] = true;
	_lightsStatus[GL_LIGHT2] = true;
	_lightsStatus[GL_LIGHT3] = true;
	_lightsStatus[GL_LIGHT4] = true;
	_lightsStatus[GL_LIGHT5] = true;
	_lightsStatus[GL_LIGHT6] = true;
	_lightsStatus[GL_LIGHT7] = true;
}

void	AreaLight::disableAllLights(int keyCode)
{
	_lightsStatus[GL_LIGHT0] = false;
	_lightsStatus[GL_LIGHT1] = false;
	_lightsStatus[GL_LIGHT2] = false;
	_lightsStatus[GL_LIGHT3] = false;
	_lightsStatus[GL_LIGHT4] = false;
	_lightsStatus[GL_LIGHT5] = false;
	_lightsStatus[GL_LIGHT6] = false;
	_lightsStatus[GL_LIGHT7] = false;
}

void	AreaLight::enableLight(int keyCode)
{
	if (ModifierKeys::getCurrentModifiers().isShiftDown())
	{
		switch (keyCode)
		{
			case 49: {_lightsStatus[GL_LIGHT0] = false; break;}
			case 50: {_lightsStatus[GL_LIGHT1] = false; break;}
			case 51: {_lightsStatus[GL_LIGHT2] = false; break;}
			case 52: {_lightsStatus[GL_LIGHT3] = false; break;}
			case 53: {_lightsStatus[GL_LIGHT4] = false; break;}
			case 54: {_lightsStatus[GL_LIGHT5] = false; break;}
			case 55: {_lightsStatus[GL_LIGHT6] = false; break;}
			case 56: {_lightsStatus[GL_LIGHT7] = false; break;}
		}
	}
	else
	{
		switch (keyCode)
		{
			case 49: {_lightsStatus[GL_LIGHT0] = true; break;}
			case 50: {_lightsStatus[GL_LIGHT1] = true; break;}
			case 51: {_lightsStatus[GL_LIGHT2] = true; break;}
			case 52: {_lightsStatus[GL_LIGHT3] = true; break;}
			case 53: {_lightsStatus[GL_LIGHT4] = true; break;}
			case 54: {_lightsStatus[GL_LIGHT5] = true; break;}
			case 55: {_lightsStatus[GL_LIGHT6] = true; break;}
			case 56: {_lightsStatus[GL_LIGHT7] = true; break;}
		}
	}
}

void	AreaLight::keyEvent(int keyCode)
{
	ToggleKey tk = _keyEvents[keyCode];
	if (tk != NULL)
		(this->*tk)(keyCode);
}