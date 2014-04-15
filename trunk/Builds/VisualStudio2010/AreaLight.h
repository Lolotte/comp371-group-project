#pragma once

#include <map>

class AreaLight
{
public:
	AreaLight(void);
	~AreaLight(void);

	void initialize();
	void render();
	void keyEvent(int keyCode);

private:
	void initializeKeys();
	void enableAllLights(int);
	void disableAllLights(int);
	void enableLight(int);

	typedef void (AreaLight::*ToggleKey)(int);

	std::map<GLenum, bool> _lightsStatus;
	std::map<int, ToggleKey> _keyEvents;
};

