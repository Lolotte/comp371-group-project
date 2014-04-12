#pragma once
#include "JuceHeader.h"
#include "Shapes.h"
#include <vector>

class OpenGLCanvas : public Component, public OpenGLRenderer
{
public:
	OpenGLCanvas(void);
	~OpenGLCanvas(void);

	void initialize();
	void addPrimitive(ADrawable *);
	virtual void renderOpenGL();
	virtual void newOpenGLContextCreated ();
	virtual void openGLContextClosing ();
	
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
};


void	OpenGLCanvas::setTextureMapping(bool value) {_textureMapping = value;}
void	OpenGLCanvas::setTextureMapping(bool value, File file) {_textureMapping = value; _textureFile = file;}
void	OpenGLCanvas::setBumpMapping(bool value) {_bumpMapping = value;}
void	OpenGLCanvas::setAntiAliasing(bool value) {_antiAliasing = value;}
void	OpenGLCanvas::setShadowMapping(bool value) {_shadowMapping = value;}
void	OpenGLCanvas::setAreaLighting(bool value) {_areaLighting = value;}

