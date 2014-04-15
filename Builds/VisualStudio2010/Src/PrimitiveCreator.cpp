#include "PrimitiveCreator.h"
#include "Shapes.h"

PrimitiveCreator::PrimitiveCreator(Rect<int> const& bounds, OpenGLCanvas *openGLCanvas)
	: _bounds(bounds), _openGLCanvas(openGLCanvas)
{
	setBounds(bounds.x, bounds.y, bounds.width, bounds.height);
}


PrimitiveCreator::~PrimitiveCreator(void)
{
	deleteAllChildren();
}

void PrimitiveCreator::initialize()
{
	_createPrimLabel = new Label("Creation of primitives");
	_createPrimLabel->setText("Creation of primitives", NotificationType::dontSendNotification);
	_createPrimLabel->setBounds(0, 0, _bounds.width, 50);
	_createPrimLabel->setFont(Font(16, Font::FontStyleFlags::bold));
	addAndMakeVisible(_createPrimLabel);

	_primitivesChoices = new ComboBox;
	_primitivesChoices->addItem("Cube", 1);
	_primitivesChoices->addItem("Teapot", 2);
	_primitivesChoices->addItem("Sphere", 3);
	_primitivesChoices->addItem("Torus", 4);
	_primitivesChoices->addItem("Cone", 5);
	_primitivesChoices->addItem("Tetrahedron", 6);
	_primitivesChoices->setBounds(0, _createPrimLabel->getBounds().getY() + _createPrimLabel->getBounds().getHeight(), 100, 30);
	addAndMakeVisible(_primitivesChoices);

	_createButton = new TextButton;
	_createButton->addListener(this);
	_createButton->setButtonText("Create");
	_createButton->setBounds(10, _primitivesChoices->getBounds().getY() + _primitivesChoices->getBounds().getHeight() + 2, 80, 30);
	addAndMakeVisible(_createButton);
}

void	PrimitiveCreator::buttonClicked(Button *button)
{
	if (button == _createButton)
		this->createPrimitive(_primitivesChoices->getSelectedId());
}

void	PrimitiveCreator::createPrimitive(int id)
{
	ADrawable *shape;

	if (_primitivesChoices->getText().isEmpty())
		return;

	switch (id)
	{
	case 1:
		{
			shape = new Cube;
			break;
		}
	case 2:
		{
			shape = new Teapot;
			break;
		}
	case 3:
		{
			shape = new Sphere;
			break;
		}
	case 4:
		{
			shape = new Torus;
			break;
		}
	case 5:
		{
			shape = new Cone;
			break;
		}
	case 6:
		{
			shape = new Tetrahedron;
			break;
		}
	}
	_openGLCanvas->addPrimitive(shape);
}
