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
   
    void update(SDL_Event* event);
};

