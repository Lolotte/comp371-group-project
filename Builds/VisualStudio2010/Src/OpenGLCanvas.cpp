#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "OpenGLCanvas.h"

OpenGLCanvas::OpenGLCanvas(void)
	: _isInitialized(false)
{
	_contextOpenGL.setRenderer (this);
    _contextOpenGL.attachTo (*this);
    _contextOpenGL.setContinuousRepainting (true);
	setBounds(0, 0, 900, 768);
}


OpenGLCanvas::~OpenGLCanvas(void)
{
	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
		delete *it;
	_contextOpenGL.detach();
}

void OpenGLCanvas::initialize()
{
	addMouseListener(this, true);
	addKeyListener(this);
	this->setupLights();
}

// Mouse listener
void OpenGLCanvas::mouseDrag(const MouseEvent &event)
{
}

void OpenGLCanvas::mouseEnter(const MouseEvent &event)
{
}

void OpenGLCanvas::mouseDown(const MouseEvent &event)
{
}

void OpenGLCanvas::mouseWheelMove(const MouseEvent &event)
{
}

void OpenGLCanvas::mouseExit (const MouseEvent &event)
{
}

void OpenGLCanvas::mouseDoubleClick (const MouseEvent &event)
{
}

// key listener
bool 	OpenGLCanvas::keyPressed (const KeyPress &key, Component *originatingComponent)
{
	return true;
}

bool 	OpenGLCanvas::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{
	return true;
}


void OpenGLCanvas::setupLights()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	GLfloat light_position1[] = { -5, 0, 5, 0 };
	GLfloat light1[] = { 1, 1, 1, 1 };
	GLfloat light2[] = { 0.5, 0.5, 0.5, 1.0 };

	//ambient light is reflected environmental light 
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 0 };

	// setup 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
	glShadeModel(GL_SMOOTH);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light2);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	
	glEnable(GL_LIGHT0);	
    glEnable(GL_LIGHTING);

	glPopMatrix();
}

void OpenGLCanvas::renderOpenGL()
{

	if (!_isInitialized)
	{
		this->initialize();
		_isInitialized = true;
	}
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glEnable(GL_DEPTH_TEST);

	// Matrix setup
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 900, 768);
	glLoadIdentity();
	gluPerspective(40, (float)900 / (float)768, 0.1, 1000);

	// Matrix setup
	glMatrixMode(GL_MODELVIEW);

	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
	{
		(*it)->setupMaterials();
		(*it)->draw();
	}
}

void OpenGLCanvas::newOpenGLContextCreated ()
{
}

void OpenGLCanvas::openGLContextClosing ()
{
}

void OpenGLCanvas::addPrimitive(ADrawable *shape)
{
	_primitives.push_back(shape);
}
