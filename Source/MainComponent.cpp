/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (1024, 768);
	_canvasOpenGL = new OpenGLCanvas;
	addAndMakeVisible(_canvasOpenGL);
	_gui = new GUI(Rect<int>(900, 0, 124, 768), _canvasOpenGL);
	_gui->initialize();
	addAndMakeVisible(_gui);
}

MainContentComponent::~MainContentComponent()
{
	deleteAllChildren();
}

void MainContentComponent::paint (Graphics& g)
{
	_gui->update();
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
