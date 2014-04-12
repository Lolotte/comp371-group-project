#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DataStructures.hpp"
#include "OpenGLCanvas.h"

class PrimitiveCreator : public Component, public ButtonListener
{
public:
	PrimitiveCreator(Rect<int> const& bounds, OpenGLCanvas *openGLCanvas);
	~PrimitiveCreator(void);

	void initialize();
	void buttonClicked(Button *);

private:
	void createPrimitive(int id);

	Rect<int> _bounds;
	OpenGLCanvas *_openGLCanvas;
	Label* _createPrimLabel;
	ComboBox *_primitivesChoices;
	TextButton *_createButton;
};

