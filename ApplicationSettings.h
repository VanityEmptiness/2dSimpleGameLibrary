#pragma once
#include <string>

namespace ApplicationSettings
{
	inline const std::string window_name = "2D Game by Vanity";
	inline const bool is_debugging = true;

	namespace VideoSettings
	{
		inline const float default_window_width = 1920;
		inline const float default_window_height = 980;
		inline const bool enable_vsync = false;
		inline const bool is_resizable = false;
	}
	
	namespace DebugMenuSettings
	{
		inline const float font_size = 14;
	}
}