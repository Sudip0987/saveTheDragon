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
#include<time.h>
#include "Pipes.hpp"
#include "KeyboardHandler.hpp"
#include "Ground.hpp"

using namespace std;

const int WIN_HEIGHT=700;
const int WIN_WIDTH=1000;
const int HERO_VELOCITY=320;
const int PIPE_VElOCITY = -120;
const int MIN_VERTICAL_SPACING=600;
const int MAX_VERTICAL_SPACING=1000;
const int hW=128;
const int PIPE_HORIZONTAL_SPACING=280;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//texture pointer
SDL_Texture* texture;


//for text rendering
SDL_Surface* textSurface;
SDL_Texture* textTexture;
TTF_Font* font;
SDL_Rect textDestination;


//function for drawing text
void drawText(string text,int x, int y,int fontSize){
    if(font==NULL)
        font  = TTF_OpenFont("Halo3.ttf", fontSize);
    
    SDL_Color textColor = {6, 50, 0,33};
    
    //create a surface using this font to display text
    textSurface = TTF_RenderText_Blended(font,text.c_str(), textColor);
    textTexture =SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    textDestination.x = x;
    textDestination.y=y;
    //get width and height from texture and set it for the destination
    SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);
    
}

void addImages(){

    
    
}

void setPipeVerticalPosition(Pipes* topPipe, Pipes* bottomPipe,int horizontalPos){
    int topPos=0,bottomPos=0,verticalSpacing=0;
    topPos = rand()% 400 +(-400);
    bottomPos = rand()% ((600-200)+1)+200;
    verticalSpacing = (-topPos)+bottomPos;
    
    //while(!((verticalSpacing>=MIN_VERTICAL_SPACING)and (verticalSpacing<=MAX_VERTICAL_SPACING))){
    while(!(verticalSpacing==MIN_VERTICAL_SPACING)){
        topPos = rand()% 450 +(-450);
        bottomPos = rand()% ((550-200)+1)+200;
        verticalSpacing = (-topPos)+bottomPos;
        
    }
    topPipe->setPosition(Vector(horizontalPos,topPos));
    bottomPipe->setPosition(Vector(horizontalPos,bottomPos));
    
    
}


int main(int argc, char **argv)
{
    clock_t start = clock();
    // Execuatable code
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    
    printf("Time elapsed in ms: %f", elapsed);

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
                              SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
    
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
    
    
    

    
    
     //copy the height of our texture
    //LOAD UP WHATEVER ASSETS HERE AFTER INIT
    

    
    
    //RUN TEXTURE
    //this time, lets make a source rectangle copying just 1 frame in size at a time
    SDL_Rect runClipRect = { 0, 0, 32, 32 }; //x:0, y:0, w: 32, h:32
    SDL_Rect runDestRect = { 0, 0, 128, 128 }; //x y, get image to bottom right of screen. w/h match clip/frame size
    
    SDL_Surface* runSurface = IMG_Load("newDragon.png");
    
    //mapRGB just does its best to find closest match to a surfaces pixel format
    SDL_PixelFormat* myPixelFormat=runSurface->format;

    //now convert to texture
    SDL_Texture* runSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, runSurface);
    //free the surface :O
    SDL_FreeSurface(runSurface);
    
    //Animation Objects
    Animation anim(runSpriteSheetWithNoBG, renderer, 8, 129, 128, 0.085);
    
    
    //setup time stuff
    Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time
    
    //list of game entities
    list<Entity*> entities;
    Entity::entities = &entities;
    
    //build hero
    Hero* hero = new Hero();
    hero->setAnimation(&anim);
    hero->setRenderer(renderer);
    Vector heroStartPos(250, 200);
    hero->setPosition(heroStartPos);
  
    
  
    
    entities.push_back(hero);
    
    SDL_Surface* pipeImage = SDL_LoadBMP("pipes.bmp");
    SDL_Texture* pipeTexture = SDL_CreateTextureFromSurface(renderer, pipeImage);
    //creating the floors and add them to entities
    
    
    
    int horizontalPos=1000;
    
    //initializing random number
    srand((unsigned int)time(NULL));

    for(int i=0;i<300;i++){
        
        
        
        horizontalPos = horizontalPos+PIPE_HORIZONTAL_SPACING;
        Pipes* topPipe = new Pipes(50,500);
        topPipe->pipeTop=true;
        topPipe->texture = pipeTexture;
        topPipe->setRenderer(renderer);
        //topPipe->setPosition(Vector(horizontalPos,0));
        topPipe->velocity.x=PIPE_VElOCITY;
        
        entities.push_back(topPipe);
        
        //floor
      /**/
        
        
        Pipes* bottomPipe = new Pipes(50,500);
        bottomPipe->setRenderer(renderer);
        bottomPipe->velocity.x=PIPE_VElOCITY;
        bottomPipe->texture = pipeTexture;

        setPipeVerticalPosition(topPipe,bottomPipe,horizontalPos);
        //bottomPipe->setPosition(Vector(horizontalPos,600));
       
        entities.push_back(bottomPipe);
        
  


    }
    
    
    Pipes* floor = new Pipes(1000,200);
    floor->texture = pipeTexture;
    
    floor->setRenderer(renderer);
    floor->setPosition(Vector(-4,WIN_HEIGHT-46));
    entities.push_back(floor);
    
    
  
    
    
    bool loop = true;
    while (loop){
        
        
        
        //difference is current time running minus the last update time
        Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
        //convert into deltaTime (decimal)
        float DT = timeDiff / 1000.0; //e.g 200ms now = 0.2 for DT
        //now update lastUpdate to the current time so the next loop calculates correctly
        lastUpdate = SDL_GetTicks();
        
        //cout << "dt = " << DT << endl;
        
        //set drawing colour for the renderer, numbers are: RGBA(alpha, transparency). All values between 0-255
        SDL_SetRenderDrawColor(renderer, 179, 236, 255, 1);
        //clear screen with current draw colour
        SDL_RenderClear(renderer);
        
        //make a SDL_Rect, to describe a rectangle x,y,w,h
        SDL_Rect rect = { 100, 50, 300, 240 };
        
        //render rectangle to screen (renderer and a rectangle for positioning)
        SDL_RenderFillRect(renderer, &rect);
        
        
        //lets do animation stuff here:
        int const runNumOfFrames = 3;
        runClipRect.x = runClipRect.w*int((SDL_GetTicks() / 100) % runNumOfFrames);
        
        //DEAL WITH USER INPUT
        //we check what kind of user input events have happened since our last check
        SDL_Event e;
        //loops through all events and temporarily stores event details in an SDL_Event object
        while (SDL_PollEvent(&e))
        {
            //check if user has clicked on the close window button
            if (e.type == SDL_QUIT){
                //exit our loop,
                loop = false;
            }
            //check if user has 'pressed' a button(not held)
            if (e.type == SDL_KEYDOWN){
                //see if ESC key was pressed
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    //exit loop
                    loop = false;
                }
                //if press up
                
                
            }
            
            
            
        }
        
       

        
            KeyboardHandler kh;
            kh.hero=hero;
            kh.update(&e);
        
        
        
        
        //loop through and update and draw all entities
        for (list<Entity*>::iterator eIt = entities.begin(); eIt != entities.end(); eIt++){
            (*eIt)->update(DT);
            (*eIt)->draw();
        }
        
        //get renderer to output to the window
        SDL_SetRenderDrawColor(renderer, 179, 236, 255, 1);
        
        SDL_RenderPresent(renderer);
        
        //sdl_ticks checks how many milliseconds since we started running our game
        /*if (SDL_GetTicks() > 5000)
         {
         loop = false;
         }*/
    }
    
    //clean up any game objects
    delete hero;
    
    //clean up renderer and window properly (aka clean up dynamic memory)
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //shut down subsystems and cleanup any setup it did earlier in sdl_init
    SDL_Quit();
    
    system("pause");
    
    
    
    return 0;
}



