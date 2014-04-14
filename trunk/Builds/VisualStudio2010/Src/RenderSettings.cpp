#include "RenderSettings.h"
#include "Jittering.h"

RenderSettings::RenderSettings(Rect<int> const& bounds, OpenGLCanvas *openGLCanvas)
	: _bounds(bounds), _openGLCanvas(openGLCanvas)
{
	setBounds(bounds.x, bounds.y, bounds.width, bounds.height);
}


RenderSettings::~RenderSettings(void)
{
	deleteAllChildren();
}

void	RenderSettings::initialize()
{
	_settingsLabel = new Label;
	_settingsLabel->setText("Render settings", NotificationType::dontSendNotification);
	_settingsLabel->setFont(Font(16, Font::FontStyleFlags::bold));
	_settingsLabel->setBounds(0, 0, _bounds.width, 30);
	addAndMakeVisible(_settingsLabel);

	_shadowMapping = new ToggleButton("Shadow mapping");
	_shadowMapping->addListener(this);
	_shadowMapping->setBounds(0, _settingsLabel->getY() + _settingsLabel->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_shadowMapping);

	_bumpMapping = new ToggleButton("Bump mapping");
	_bumpMapping->addListener(this);
	_bumpMapping->setBounds(0, _shadowMapping->getY() + _shadowMapping->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_bumpMapping);
	
	_antiAliasing = new ToggleButton("Anti-aliasing");
	_antiAliasing->addListener(this);
	_antiAliasing->setBounds(0, _bumpMapping->getY() + _bumpMapping->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_antiAliasing);

	_intensityAA = new Slider;
	_intensityAA->setRange(1, Jittering::MAX_ITERATIONS);
	_intensityAA->setValue(8);
	_intensityAA->addListener(this);
	_intensityAA->setBounds(0, _antiAliasing->getY() + _antiAliasing->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_intensityAA);

	_areaLighting = new ToggleButton("Area lighting");
	_areaLighting->addListener(this);
	_areaLighting->setBounds(0, _intensityAA->getY() + _intensityAA->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_areaLighting);

	_textureMapping = new ToggleButton("Texture mapping");
	_textureMapping->addListener(this);
	_textureMapping->setBounds(0, _areaLighting->getY() + _areaLighting->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_textureMapping);

	_browseButton = new TextButton;
	_browseButton->addListener(this);
	_browseButton->setButtonText("Choose texture");
	_browseButton->setBounds(0, _textureMapping->getY() + _textureMapping->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_browseButton);

	_textureName = new Label;
	_textureName->setText("N/A", NotificationType::dontSendNotification);
	_textureName->setBounds(0, _browseButton->getY() + _browseButton->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_textureName);

	_materialsOn = new ToggleButton("Materials");
	_materialsOn->setToggleState(true, NotificationType::dontSendNotification);
	_materialsOn->addListener(this);
	_materialsOn->setBounds(0, _textureName->getY() + _textureName->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_materialsOn);

	_materialColorSelector = new ColourSelector;
	_materialColorSelector->addChangeListener(this);
	_materialColorSelector->setBounds(0, _materialsOn->getY() + _materialsOn->getHeight(), _bounds.width, 120);
	addAndMakeVisible(_materialColorSelector);

	_specularColorSelector = new ColourSelector;
	_specularColorSelector->addChangeListener(this);
	_specularColorSelector->setBounds(0, _materialColorSelector->getY() + _materialColorSelector->getHeight(), _bounds.width, 120);
	addAndMakeVisible(_specularColorSelector);

	_shininess = new Slider;
	_shininess->setRange(0, 128);
	_shininess->setValue(125);
	_shininess->addListener(this);
	_shininess->setBounds(0, _specularColorSelector->getY() + _specularColorSelector->getHeight(), _bounds.width, 30);
	addAndMakeVisible(_shininess);


	this->initializeListeners();
}

void RenderSettings::initializeListeners()
{
	_buttonListeners[_textureMapping] = &RenderSettings::getTextureFile;
	_buttonListeners[_shadowMapping] = &RenderSettings::setShadowMapping;
	_buttonListeners[_antiAliasing] = &RenderSettings::setAntiAliasing;
	_buttonListeners[_bumpMapping] = &RenderSettings::setBumpMapping;
	_buttonListeners[_areaLighting] = &RenderSettings::setAreaLighting;
	_buttonListeners[_browseButton] = &RenderSettings::getTextureFile;
	_buttonListeners[_materialsOn] = &RenderSettings::enableMaterials;
}

void RenderSettings::changeListenerCallback(ChangeBroadcaster* broadcaster)
{
	if (broadcaster == _materialColorSelector)
		_openGLCanvas->setDiffuseMaterial(_materialColorSelector->getCurrentColour());
}

void RenderSettings::update()
{
	if (_textureMapping->getToggleState() && !_browseButton->isEnabled())
		_browseButton->setEnabled(true);
	else if (!_textureMapping->getToggleState() && _browseButton->isEnabled())
	{
		_openGLCanvas->setTextureMapping(false);
		_browseButton->setEnabled(false);
		_textureName->setText("N/A", NotificationType::dontSendNotification);
	}
}

void 	RenderSettings::sliderValueChanged (Slider *slider)
{
	if (slider == _intensityAA)
	{
		Jittering::MAX_ITERATIONS = static_cast<int>(slider->getValue());
		if (Jittering::MAX_ITERATIONS == 0)
			Jittering::MAX_ITERATIONS = 1;
	}
	else if (slider == _shininess)
		_openGLCanvas->setShininess(slider->getValue());
}

void  RenderSettings::buttonClicked (Button* button)
{
	(this->*_buttonListeners[button])();
}

void	RenderSettings::getTextureFile()
{
	if (_textureMapping->getToggleState())
	{
		FileChooser fileChooser("Texture file browser");
		fileChooser.browseForFileToOpen();
		_textureFile = fileChooser.getResult();
		_textureName->setText(_textureFile.getFileName(), NotificationType::dontSendNotification);
		_openGLCanvas->setTextureMapping(true, _textureFile);
	}
	else
		_openGLCanvas->setTextureMapping(false, _textureFile);
}

void	RenderSettings::setShadowMapping()
{
	_openGLCanvas->setShadowMapping(_shadowMapping->getToggleState());
}

void	RenderSettings::setBumpMapping()
{
	_openGLCanvas->setBumpMapping(_bumpMapping->getToggleState());
}

void	RenderSettings::setAntiAliasing()
{
	_openGLCanvas->setAntiAliasing(_antiAliasing->getToggleState());
}

void	RenderSettings::setAreaLighting()
{
	_openGLCanvas->setAreaLighting(_areaLighting->getToggleState());
}

void	RenderSettings::enableMaterials()
{
	_openGLCanvas->enableMaterials(_materialsOn->getToggleState());
}
