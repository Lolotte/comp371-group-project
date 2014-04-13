#pragma once
#include "JuceHeader.h"
#include "Shapes.h"
#include "textfile.h"

#include <vector>

class OpenGLCanvas : public Component, public OpenGLRenderer, public MouseListener, public KeyListener
{
public:
	OpenGLCanvas(void);
	~OpenGLCanvas(void);

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
	virtual void mouseWheelMove(const MouseEvent &event);
	virtual void mouseExit (const MouseEvent &event);
	virtual void mouseDoubleClick (const MouseEvent &event);

	// key listener
	virtual bool 	keyPressed (const KeyPress &key, Component *originatingComponent);
	virtual bool 	keyStateChanged (bool isKeyDown, Component *originatingComponent);

	inline void setTextureMapping(bool value);
	inline void setTextureMapping(bool value, File file);
	inline void setBumpMapping(bool value);
	inline void setAntiAliasing(bool value);
	inline void setShadowMapping(bool value);
	inline void setAreaLighting(bool value);

private:
	void setupLights();

	bool _isInitialized;
	OpenGLContext _contextOpenGL;
	std::vector<ADrawable *> _primitives;
	bool _textureMapping;
	bool _bumpMapping;
	bool _antiAliasing;
	bool _shadowMapping;
	bool _areaLighting;
	File _textureFile;

	bool fogToggle;
	GLfloat fogDensityStart, fogDensityEnd;
};


void	OpenGLCanvas::setTextureMapping(bool value) {_textureMapping = value;}
void	OpenGLCanvas::setTextureMapping(bool value, File file) {_textureMapping = value; _textureFile = file;}
void	OpenGLCanvas::setBumpMapping(bool value) {_bumpMapping = value;}
void	OpenGLCanvas::setAntiAliasing(bool value) {_antiAliasing = value;}
void	OpenGLCanvas::setShadowMapping(bool value) {_shadowMapping = value;}
void	OpenGLCanvas::setAreaLighting(bool value) {_areaLighting = value;}


