#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DataStructures.hpp"
#include "PrimitiveCreator.h"
#include "RenderSettings.h"

class GUI : public Component
{
public:
	GUI(Rect<int> const& bounds, OpenGLCanvas *openGLCanvas);
	~GUI(void);

	void initialize();
	void update();

private:
	Rect<int> _bounds;
	OpenGLCanvas *_openGLCanvas;
	PrimitiveCreator * _primCreator;
	RenderSettings *	_renderSettings;
};

