#pragma once
#include "SDLGameLib/Src/GameManager/SceneManager.h"

class Game
{
public:
	double delta_time; //Can't be deleted
	double fps; //Can't be deleted
	
	Game(){}
	~Game(){}

	void OnLoad(); //Can't be deleted
	void OnUpdate(); //Can't be deleted

private:
	
};

inline Game* game_handler; //Can't be deleted