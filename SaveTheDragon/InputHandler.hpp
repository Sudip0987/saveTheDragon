#pragma once
#include <SDL2/SDL.h>
#include "Hero.hpp"

class InputHandler
{
public:
	Hero* hero;


	InputHandler();
	~InputHandler();

	//abstract function
	virtual void update(SDL_Event* event) = 0;
};

