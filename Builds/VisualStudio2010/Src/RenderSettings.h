#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DataStructures.hpp"
#include "OpenGLCanvas.h"
#include <map>

class RenderSettings : public Component, public ButtonListener
{
public:
	RenderSettings(Rect<int> const& bounds, OpenGLCanvas *openGLCanvas);
	~RenderSettings(void);

	void initialize();
	void update();
	void buttonClicked (Button* button);

private:
	void initializeListeners();
	void getTextureFile();
	void setShadowMapping();
	void setBumpMapping();
	void setAntiAliasing();
	void setAreaLighting();

	typedef void (RenderSettings::*listener)(void);

	Rect<int> _bounds;
	OpenGLCanvas *_openGLCanvas;
	Label		*_settingsLabel;
	ToggleButton *_shadowMapping;
	ToggleButton *_bumpMapping;
	ToggleButton *_antiAliasing;
	ToggleButton *_areaLighting;
	ToggleButton *_textureMapping;
	TextButton	*_browseButton;
	Label *_textureName;
	File _textureFile;
	std::map<Button *, listener> _buttonListeners;
};


