#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DataStructures.hpp"
#include "OpenGLCanvas.h"
#include <map>

class RenderSettings : public Component, public ButtonListener,
						public SliderListener, public ChangeListener
{
public:
	RenderSettings(Rect<int> const& bounds, OpenGLCanvas *openGLCanvas);
	~RenderSettings(void);

	void initialize();
	void update();
	void buttonClicked (Button* button);
	virtual void 	sliderValueChanged (Slider *slider);
	virtual void changeListenerCallback(ChangeBroadcaster*);

private:
	void initializeListeners();
	void getTextureFile();
	void setShadowMapping();
	void setBumpMapping();
	void setAntiAliasing();
	void setAreaLighting();
	void enableMaterials();

	typedef void (RenderSettings::*listener)(void);

	Rect<int> _bounds;
	OpenGLCanvas *_openGLCanvas;
	Label		*_settingsLabel;
	ToggleButton *_shadowMapping;
	ToggleButton *_bumpMapping;
	ToggleButton *_antiAliasing;
	Slider		*_intensityAA;
	ToggleButton *_areaLighting;
	ToggleButton *_textureMapping;
	TextButton	*_browseButton;
	ToggleButton *_materialsOn;
	ColourSelector *_materialColorSelector;
	ColourSelector *_specularColorSelector;
	Slider		*_shininess;
	Label *_textureName;
	File _textureFile;
	std::map<Button *, listener> _buttonListeners;
};


