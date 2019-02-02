#pragma once
#include "InputHandler.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "GameStateMachine.hpp"
#include "ConstVariables.hpp"
#include "SoundManager.hpp"

class KeyboardHandler:
public InputHandler
{
public:
    KeyboardHandler();
    ~KeyboardHandler();
   
    bool controlEnabled=true;
    const int HERO_VELOCITY=300;
    const int WIN_HEIGHT=700;

    const int PIPE_VElOCITY = -150;
    void update(SDL_Event* event);
};

