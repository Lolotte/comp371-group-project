#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "OpenGLCanvas.h"
#include "textfile.h"

bool fogToggle = false;     // Fog on/off
GLfloat fogDensityStart = 10.0f;	// Fog density
GLfloat fogDensityEnd = 20.0f;


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
	this->setWantsKeyboardFocus(true);
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

	if (key == KeyPress::escapeKey)
	{
			exit(0);
	}

	if (key.getKeyCode() == 70)
	{
		if (fogToggle)
			fogToggle = false;
		else if (!fogToggle)
			fogToggle = true;
	}
	if (key.getKeyCode() == 43)
	{
		fogDensityStart += 0.1f;
		fogDensityEnd += 0.1f;
	}
	if (key.getKeyCode() == 45)
	{
		fogDensityStart -= 0.1f;
		fogDensityEnd -= 0.1f;	
	}


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

void OpenGLCanvas::fog()
{
	GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};      // Fog Color
	GLfloat fogDensity = 0.1f;

	glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]); 
		
	glFogi(GL_FOG_MODE, GL_LINEAR);				// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);        // Fog Color
	//glFogf(GL_FOG_DENSITY, fogDensity);     // How Dense Will The Fog Be (not needed for GL_LINEAR)
	glHint(GL_FOG_HINT, GL_NICEST);         // Fog Hint Value
	glFogf(GL_FOG_START, fogDensityStart);  // Fog Start Depth
	glFogf(GL_FOG_END, fogDensityEnd);     // Fog End Depth
	glEnable(GL_FOG);						// Enables GL_FOG
}


void OpenGLCanvas::renderOpenGL()
{

	if (!_isInitialized)
	{
		this->initialize();
		_isInitialized = true;
	}

	if (fogToggle)
	{
		fog();
	}
	else if (!fogToggle)
	{
		glClearColor(0, 0, 0, 0);
		glDisable(GL_FOG);
	}

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
