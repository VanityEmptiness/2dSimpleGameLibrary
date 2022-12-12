#pragma once

#ifndef _SDL_APPLICATION_H
#define _SDL_APPLICATION_H

#include "../Vendors/Include/IMGUI/imgui.h"
#include "../Vendors/Include/IMGUI/imgui_impl_sdl.h"
#include "../Vendors/Include/IMGUI/imgui_impl_sdlrenderer.h"
#include "../Vendors/Include/SDL/SDL.h"
#include "../../ApplicationSettings.h"
#include "../../Game.h"
#include "GameManager/Events.h"
#include "GameManager/SceneManager.h"
#include "Utils/Math.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <psapi.h>
#include <cstdio>
#include <chrono>
#include <thread>

#endif 

class SDLApplication
{
public:

	SDLApplication() {};
	SDLApplication(const std::string& title, const float width, const float height);
	~SDLApplication() {};

	bool Run();
	void UpdateRender();
	static void Update();
	void Destroy();
	void RenderImgui();
	void RenderSDL();

private:

	//Window Settings 
	float width = 1280;
	float height = 720;
	const std::string window_name;
	ImVec4 background_render_clear_color = ImVec4(1.0f, 0.90f, 0.00f, 1.00f);

	//Window Handlings
	bool is_running = true;
	SDL_WindowFlags window_flags;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
};

inline SDLApplication* application;