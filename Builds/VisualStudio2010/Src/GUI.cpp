#include "GUI.h"
#include "OpenGLCanvas.h"

GUI::GUI(Rect<int> const &bounds, OpenGLCanvas *openGLCanvas)
	: _bounds(bounds), _openGLCanvas(openGLCanvas)
{
	setBounds(bounds.x, bounds.y, bounds.width, bounds.height);
}


GUI::~GUI(void)
{
	deleteAllChildren ();
}

void GUI::initialize()
{
	_primCreator = new PrimitiveCreator(Rect<int>(0, 0, _bounds.width, _bounds.height / 4), _openGLCanvas);
	_primCreator->initialize();
	addAndMakeVisible(_primCreator);

	_renderSettings = new RenderSettings(Rect<int>(0, _bounds.height / 4, _bounds.width, (int)(_bounds.height * 0.75f)), _openGLCanvas);
	_renderSettings->initialize();
	addAndMakeVisible(_renderSettings);
}

void GUI::update()
{
	_renderSettings->update();
}