#include <iostream>
//#include <Windows.h>
#include "glew\include\GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "OpenGLCanvas.h"
#include "textfile.h"
#include "Jittering.h"

bool fogToggle = false;     // Fog on/off
GLfloat fogDensityStart = 10.0f;	// Fog density
GLfloat fogDensityEnd = 20.0f;


OpenGLCanvas::OpenGLCanvas(void)
	: _isInitialized(false), _textureMapping(false), _bumpMapping(false),
	_antiAliasing(false), _shadowMapping(false), _areaLighting(false)
{
	_contextOpenGL.setRenderer (this);
    _contextOpenGL.attachTo (*this);
    _contextOpenGL.setContinuousRepainting (true);
	setBounds(0, 0, 850, 768);
	_shadersManager = new ShadersManager(_contextOpenGL);
	_textureMappingManager = new TextureMapping;
	_mainCamera = new Camera;
	_areaLight = new AreaLight;
}


OpenGLCanvas::~OpenGLCanvas(void)
{
	delete _areaLight;
	delete _mainCamera;

	_shadersManager->release();
	delete _shadersManager;

	delete _textureMappingManager;

	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
		delete *it;
	_contextOpenGL.detach();
}

void OpenGLCanvas::initialize()
{
	glewInit();
	addMouseListener(this, true);
	addKeyListener(this);
	this->setWantsKeyboardFocus(true);
	_areaLight->initialize();
	//this->setupLights();
	this->setWantsKeyboardFocus(true);
	this->initializeKeys();
	fogToggle = false;			 // Fog on/off
	fogDensityStart = 10.0f;	// Fog density startpoint
	fogDensityEnd = 20.0f;		// Fog density endpoint

	
	_shadersManager->addShader("textureMapping.frag", "textureMapping.vert");
	//_shadersManager->addShader("myShader.frag", "myShader.vert");
	//_shadersManager->addShader("phong.frag", "phong.vert");
}

void OpenGLCanvas::initializeKeys()
{
	_keyEvents[44] = &OpenGLCanvas::selectPreviousItem;
	_keyEvents[46] = &OpenGLCanvas::selectNextItem;
	_keyEvents[70] = &OpenGLCanvas::activateFog;
	_keyEvents[43] = &OpenGLCanvas::increaseFogDensity;
	_keyEvents[45] = &OpenGLCanvas::decreaseFogDensity;
	_keyEvents[65] = &OpenGLCanvas::rotateCameraLeft;
	_keyEvents[68] = &OpenGLCanvas::rotateCameraRight;
	_keyEvents[87] = &OpenGLCanvas::moveForward;
	_keyEvents[83] = &OpenGLCanvas::moveBackward;
	_keyEvents[88] = &OpenGLCanvas::rotateCameraTop;
	_keyEvents[89] = &OpenGLCanvas::rotateCameraBottom;
	_keyEvents[67] = &OpenGLCanvas::strafeLeft;
	_keyEvents[86] = &OpenGLCanvas::strafeRight;
	_keyEvents[82] = &OpenGLCanvas::reset;
	_keyEvents[KeyPress::upKey] = &OpenGLCanvas::moveSelectedObjectFwdTop;
	_keyEvents[KeyPress::downKey] = &OpenGLCanvas::moveSelectedObjectBackBottom;
	_keyEvents[KeyPress::leftKey] = &OpenGLCanvas::moveSelectedObjectLeft;
	_keyEvents[KeyPress::rightKey] = &OpenGLCanvas::moveSelectedObjectRight;
}

// key events
void OpenGLCanvas::rotateCameraLeft()
{
	_mainCamera->rotateY(5.0);
	repaint();
}

void OpenGLCanvas::rotateCameraRight()
{
	_mainCamera->rotateY(-5.0);
	repaint();
}

void OpenGLCanvas::moveForward()
{
	_mainCamera->moveForwards( -0.1 ) ;
	repaint();
}

void OpenGLCanvas::moveBackward()
{
	_mainCamera->moveForwards( 0.1 ) ;
	repaint();
}

void OpenGLCanvas::rotateCameraTop()
{
	_mainCamera->rotateX(5.0);
	repaint();
}

void OpenGLCanvas::rotateCameraBottom()
{
	_mainCamera->rotateX(-5.0);
	repaint();
}

void OpenGLCanvas::strafeLeft()
{
	_mainCamera->strafeRight(-0.1);
	repaint();
}

void OpenGLCanvas::strafeRight()
{
	_mainCamera->strafeRight(0.1);
	repaint();
}

// a changer
void OpenGLCanvas::reset()
{
	_mainCamera->move(Vector3<GLfloat>(0.0,0.3,0.0));
	repaint();
}

void OpenGLCanvas::moveSelectedObjectFwdTop()
{
	if (ModifierKeys::getCurrentModifiers().isShiftDown())
		_selectedObject->move(Vector3<GLfloat>(0, 0, -0.1));
	else
		_selectedObject->move(Vector3<GLfloat>(0, 0.1, 0));
	repaint();
}

void OpenGLCanvas::moveSelectedObjectBackBottom()
{
	if (ModifierKeys::getCurrentModifiers().isShiftDown())
		_selectedObject->move(Vector3<GLfloat>(0, 0, 0.1));
	else
		_selectedObject->move(Vector3<GLfloat>(0, -0.1, 0));
	repaint();
}

void OpenGLCanvas::moveSelectedObjectLeft()
{
	_selectedObject->move(Vector3<GLfloat>(-0.1f, 0, 0));
	repaint();
}

void OpenGLCanvas::moveSelectedObjectRight()
{
	_selectedObject->move(Vector3<GLfloat>(0.1f, 0, 0));
	repaint();
}

void OpenGLCanvas::selectPreviousItem()
{
	std::vector<ADrawable *>::iterator it;
	it = _primitives.begin();
	
	(*it)->selected = false;
	if (it != _primitives.begin())
		it--;
	else
		it = _primitives.end() - 1;
	(*it)->selected = true;
	_selectedObject = *it;
}

void OpenGLCanvas::selectNextItem()
{
	std::vector<ADrawable *>::iterator it;
	it = _primitives.begin();

	(*it)->selected = false;
	if (it != _primitives.end() - 1)
		it++;
	else
		it = _primitives.begin();
	(*it)->selected = true;
	_selectedObject = *it;
}

void OpenGLCanvas::activateFog()
{
	fogToggle = !fogToggle;
}

void OpenGLCanvas::increaseFogDensity()
{
	fogDensityStart += 0.1f;
	fogDensityEnd += 0.1f;
}

void OpenGLCanvas::decreaseFogDensity()
{
	fogDensityStart -= 0.1f;
	fogDensityEnd -= 0.1f;	
}

// Mouse listener
void OpenGLCanvas::mouseDrag(const MouseEvent &event)
{
	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
	{
		if ((*it)->selected){
			//if (event.mods.isRightButtonDown())
			//	(*it)->move(event.getDistanceFromDragStartX(), event.getDistanceFromDragStartY());
			if (event.mods.isLeftButtonDown())
				(*it)->rotate(event.getDistanceFromDragStartX(), event.getDistanceFromDragStartY());
			if (event.mods.isMiddleButtonDown())
				(*it)->scale(event.getDistanceFromDragStartY());
		}
	}
	renderOpenGL();
	repaint();
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
		JUCEApplication::quit();
	
	ToggleKey tk = _keyEvents[key.getKeyCode()];
	if (tk != NULL)
		(this->*tk)();
	_areaLight->keyEvent(key.getKeyCode());
	renderOpenGL();
	repaint();
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
	if (_textureMapping)
		_textureMappingManager->loadTexture(_textureFile.getFullPathName());
	if (_shadersManager->isActive())
		_shadersManager->use();

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

	if (_antiAliasing)
		this->applyAntiAliasing();
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glEnable(GL_DEPTH_TEST);

		// Matrix setup
		glMatrixMode(GL_PROJECTION);
		glViewport(0, 0, 900, 768);
		glLoadIdentity();
		gluPerspective(40, (float)900 / (float)768, 0.1, 1000);

		// Matrix setup
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		_mainCamera->render();
		_areaLight->render();
		
		if (_textureMapping)
			_textureMappingManager->apply(_shadersManager->getProgramID());

		std::vector<ADrawable *>::iterator it;
		for (it = _primitives.begin(); it != _primitives.end(); ++it)
		{
			if (_materialsOn)
				(*it)->setupMaterials();
			else 
				(*it)->resetMaterials();
			(*it)->draw();
		}
		glPopMatrix();
	}
}

void	OpenGLCanvas::setDiffuseMaterial(Colour diffuseColour)
{
	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
	{
		if (_materialsOn)
			(*it)->setupMaterials(ADrawable::MaterialType::DIFFUSE, diffuseColour);
	}
}

void	OpenGLCanvas::setShininess(double value)
{
	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
	{
		if (_materialsOn)
			(*it)->setShininess(value);
	}
}

void	OpenGLCanvas::setSpecularMaterial(Colour specularColour)
{
	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
	{
		if (_materialsOn)
			(*it)->setupMaterials(ADrawable::MaterialType::SPECULAR, specularColour);
	}
}

void	OpenGLCanvas::enableMaterials(bool value)
{
	_materialsOn = value;
}

void	OpenGLCanvas::setTextureMapping(bool value, File file)
{
	_textureMapping = value;
	_textureFile = file;
}

void OpenGLCanvas::drawPrimitives()
{
	std::vector<ADrawable *>::iterator it;
	for (it = _primitives.begin(); it != _primitives.end(); ++it)
	{
		(*it)->setupMaterials();
		(*it)->draw();
	}
}

void OpenGLCanvas::applyAntiAliasing()
{
	GLint viewport[4];
	int iterations;
	Jittering jitter;

	glGetIntegerv (GL_VIEWPORT, viewport);

	glClear(GL_ACCUM_BUFFER_BIT);
	for (iterations = 0; iterations < Jittering::MAX_ITERATIONS; iterations++)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		jitter.accPerspective (40.0, 900.0/768.0, 0.1, 1000.0, JITTER8[iterations].x, JITTER8[iterations].y, 0.0, 0.0, 1.0);
		this->drawPrimitives();
		glAccum(GL_ACCUM, 1.0/ Jittering::MAX_ITERATIONS);
	}
	glAccum (GL_RETURN, 1.0);
	glFlush();
}

void OpenGLCanvas::newOpenGLContextCreated ()
{
}

void OpenGLCanvas::openGLContextClosing ()
{
}

void OpenGLCanvas::addPrimitive(ADrawable *shape)
{
	_selectedObject = shape;
	_primitives.push_back(shape);
}
