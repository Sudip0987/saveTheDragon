#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Animation.hpp"
#include "Entity.hpp"
#include "Hero.hpp"
#include <list>
#include <ctime>
#include <cstdlib>
#include "Pipes.hpp"
#include "KeyboardHandler.hpp"
#include "GlobalGameState.hpp"
#include "GamePlayScreenState.hpp"
#include "MenuScreenState.hpp"
#include "ConstVariables.hpp"
#include "GameOverScreen.hpp"
#include "SoundManager.hpp"
using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//texture pointer
SDL_Texture* texture;


//for text rendering
SDL_Surface* textSurface;
SDL_Texture* textTexture;
TTF_Font* font;
SDL_Rect textDestination;




int main(int argc, char **argv)
{
   
   
    //initiate SDL with the subsystems you want to use ie SDL_INIT_VIDEO
    
    //we're initaliasing all of them (sound, input, video etc)
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL Fail initialised!!!\n";
        return -1; //failed, dont continue rest of main code
    }
    else
    {
        cout << "SDL initialised success!!!\n";
    }
    
    //NEED TO INIT SDL_Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        cout << "sdl image did not load: " << IMG_GetError() << endl;
        SDL_Quit();
        system("pause");
        return -1;
    }
    //SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
        cout << "mixer didn't initialise" << endl;
        SDL_Quit();
        system("pause");
        return -1;
    }
    //create window
    window = SDL_CreateWindow("Save The Dragon", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, ConstVariables::WIN_WIDTH, ConstVariables::WIN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
    
    if (window != NULL){
        cout << "Window created!" << endl;
    }
    else
    {
        cout << "Failed to create window!" << endl;
        return -1;
    }
    
    //create renderer to help draw stuff to the screen
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer != NULL)
    {
        cout << "Renderer created!" << endl;
    }
    else
    {
        cout << "Renderer FAILED!" << endl;
        return -1;
    }
    
    if(TTF_Init()!=0){
        cout <<"SDL TTF Failed"<<endl;
        system("pause");
        SDL_Quit();
        return -1;
        
    }
    Mix_Music* music = Mix_LoadMUS("music.ogg");
    if (music == NULL){
        cout << "Music failed to load!" << endl;
        SDL_Quit();
        system("pause");
        return -1;
    }
    Mix_PlayMusic(music, -1);
    

    SoundManager::soundManager.loadSound("fly", "flySound.wav");
    SoundManager::soundManager.loadSound("background", "bgMusic.wav");
    SoundManager::soundManager.loadSound("die", "die.wav");
    SoundManager::soundManager.loadSound("points", "points.wav");



    GlobalGameState::renderer = renderer;
    
    // showScreen();
    
    
 
        GlobalGameState::gameStateMachine.pushState(new MenuScreenState());

    
    bool loop = true;
    while (loop){
        
        GlobalGameState::gameStateMachine.update();
        GlobalGameState::gameStateMachine.render();
        
        if (GlobalGameState::quitGame || GlobalGameState::gameStateMachine.gameStates.empty())
            loop = false;
    }
    //clean up any extra screen game states
    GlobalGameState::gameStateMachine.clearAll();
    
    //cleanup font
 
    
    //clean up renderer and window properly (aka clean up dynamic memory)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //shut down subsystems and cleanup any setup it did earlier in sdl_init
    SDL_Quit();
    
    system("pause");
    
    return 0;
}
