#pragma once
#include "JuceHeader.h"
#include "Shapes.h"
#include "textfile.h"
#include "ShadersManager.h"
#include "TextureMapping.h"
#include "Camera.h"
#include "AreaLight.h"
#include "Arcball.h"

#include <map>

class OpenGLCanvas : public Component, public OpenGLRenderer, public MouseListener, public KeyListener
{
public:
	OpenGLCanvas(void);
	~OpenGLCanvas(void);

	void initializeKeys();
	void initialize();
	void addPrimitive(ADrawable *);
	virtual void renderOpenGL();
	virtual void newOpenGLContextCreated ();
	virtual void openGLContextClosing ();
	virtual void fog();

	// Mouse listener
	virtual void mouseDrag(const MouseEvent &event);
	virtual void mouseEnter(const MouseEvent &event);
	virtual void mouseDown(const MouseEvent &event);
	virtual void mouseUp(const MouseEvent &event);
	virtual void mouseWheelMove(const MouseEvent &event);
	virtual void mouseExit (const MouseEvent &event);
	virtual void mouseDoubleClick (const MouseEvent &event);

	// key listener
	virtual bool 	keyPressed (const KeyPress &key, Component *originatingComponent);
	virtual bool 	keyStateChanged (bool isKeyDown, Component *originatingComponent);

	void setShininess(double value);
	void setDiffuseMaterial(Colour diffuseColor);
	void setSpecularMaterial(Colour specularColor);
	void enableMaterials(bool value);
	void setTextureMapping(bool value, File file);
	inline void setTextureMapping(bool value);
	inline void setBumpMapping(bool value);
	inline void setAntiAliasing(bool value);
	inline void setShadowMapping(bool value);
	inline void setAreaLighting(bool value);
		
private:

	typedef void (OpenGLCanvas::*ToggleKey)();

	void applyAntiAliasing();
	void drawPrimitives();

	
	Vector3<GLfloat> GetArcballVector(int x, int y);
	void rotateAccToArcball(int mx, int my);

	// key events
	void selectPreviousItem();
	void selectNextItem();
	void activateFog();
	void increaseFogDensity();
	void decreaseFogDensity();
	void rotateCameraLeft();
	void rotateCameraRight();
	void moveForward();
	void moveBackward();
	void rotateCameraTop();
	void rotateCameraBottom();
	void strafeLeft();
	void strafeRight();
	void reset();
	void moveSelectedObjectFwdTop();
	void moveSelectedObjectBackBottom();
	void moveSelectedObjectLeft();
	void moveSelectedObjectRight();
	
	bool _isInitialized;
	OpenGLContext _contextOpenGL;
	std::vector<ADrawable *> _primitives;
	bool _textureMapping;
	bool _bumpMapping;
	bool _antiAliasing;
	bool _shadowMapping;
	bool _areaLighting;
	bool _materialsOn;
	File _textureFile;
	ShadersManager *_shadersManager;
	TextureMapping *_textureMappingManager;
	Camera *_mainCamera;
	AreaLight *_areaLight;
	std::map<int, ToggleKey> _keyEvents;
	ADrawable *_selectedObject;
	Arcball _arcball;

	bool fogToggle;
	GLfloat fogDensityStart, fogDensityEnd;
};


void	OpenGLCanvas::setTextureMapping(bool value) {_textureMapping = value;}
void	OpenGLCanvas::setBumpMapping(bool value) {_bumpMapping = value;}
void	OpenGLCanvas::setAntiAliasing(bool value) {_antiAliasing = value;}
void	OpenGLCanvas::setShadowMapping(bool value) {_shadowMapping = value;}
void	OpenGLCanvas::setAreaLighting(bool value) {_areaLighting = value;}


