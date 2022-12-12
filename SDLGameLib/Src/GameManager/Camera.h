#pragma once
#include "../Utils/Math.h"
#include "../../../ApplicationSettings.h"

class Camera
{
public:
	Camera(){}
	~Camera(){}

	Vec2 viewport = { ApplicationSettings::VideoSettings::default_window_width / 2, ApplicationSettings::VideoSettings::default_window_height / 2 }; //Sensible Value, wrong value can cause miss rendering positioning
	Vec2 position = { ApplicationSettings::VideoSettings::default_window_width / 2, ApplicationSettings::VideoSettings::default_window_height / 2 };
	bool is_binded = false;

private:

};
