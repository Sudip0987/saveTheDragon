#include "GamePlayScreenState.hpp"


GamePlayScreenState::GamePlayScreenState()
{
    SDL_Surface* runSurface = IMG_Load("newDragon.png");
    //tell surface which colour should be invisible
    SDL_SetColorKey(runSurface, 1, SDL_MapRGB(runSurface->format, 128, 128, 255));
    //convert it to texture
    heroTexture = SDL_CreateTextureFromSurface(GlobalGameState::renderer, runSurface);
    //cleanup surface memory
    SDL_FreeSurface(runSurface);
    
    heroAnimation = new Animation(heroTexture, GlobalGameState::renderer,8, 129, 128, 0.085);
    Entity::entities = &entities;
    hero = new Hero();
    hero->setAnimation(heroAnimation);
    hero->setRenderer(GlobalGameState::renderer);
    hero->pos.x = 200;
    hero->pos.y = 200;
    
    entities.push_back(hero);
  
    keyboardHandler.hero = hero;
    
    SDL_Surface* pipeImage = SDL_LoadBMP("pipes.bmp");
    SDL_Texture* pipeTexture = SDL_CreateTextureFromSurface(GlobalGameState::renderer, pipeImage);
    //creating the floors and add them to entities
    
    
    
    int horizontalPos=1000;
    
    //initializing random number
    srand((unsigned int)time(NULL));
    
    for(int i=0;i<300;i++){
        
        
        
        horizontalPos = horizontalPos+ ConstVariables::PIPE_HORIZONTAL_SPACING;
        Pipes* topPipe = new Pipes(50,500);
        topPipe->pipeTop=true;
        topPipe->texture = pipeTexture;
        topPipe->setRenderer(GlobalGameState::renderer);
        //topPipe->setPosition(Vector(horizontalPos,0));
        topPipe->velocity.x=ConstVariables::PIPE_VElOCITY;
        
        entities.push_back(topPipe);
        
        //floor
        /**/
        
        
        Pipes* bottomPipe = new Pipes(50,500);
        bottomPipe->setRenderer(GlobalGameState::renderer);
        bottomPipe->velocity.x=ConstVariables::PIPE_VElOCITY;
        bottomPipe->texture = pipeTexture;
        
        setPipeVerticalPosition(topPipe,bottomPipe,horizontalPos);
        //bottomPipe->setPosition(Vector(horizontalPos,600));
        
        entities.push_back(bottomPipe);
        
        
        
        
    }
    
    
    Pipes* floor = new Pipes(1000,200);
    floor->texture = pipeTexture;
    
    floor->setRenderer(GlobalGameState::renderer);
    floor->setPosition(Vector(200,ConstVariables::WIN_HEIGHT-46));
    entities.push_back(floor);
    

    
    
    lastUpdate = SDL_GetTicks();
    
}

GamePlayScreenState::~GamePlayScreenState()
{
    //delete everything we need to
    delete hero;
   
    delete heroAnimation;
    SDL_DestroyTexture(heroTexture);
    
}
void GamePlayScreenState::setPipeVerticalPosition(Pipes* topPipe, Pipes* bottomPipe,int horizontalPos){
    int topPos=0,bottomPos=0,verticalSpacing=0;
    topPos = rand()% 400 +(-400);
    bottomPos = rand()% ((600-200)+1)+200;
    verticalSpacing = (-topPos)+bottomPos;
    
    //while(!((verticalSpacing>=MIN_VERTICAL_SPACING)and (verticalSpacing<=MAX_VERTICAL_SPACING))){
    while(!(verticalSpacing==600)){//TODO
        topPos = rand()% 450 +(-450);
        bottomPos = rand()% ((550-200)+1)+200;
        verticalSpacing = (-topPos)+bottomPos;
        
    }
    topPipe->setPosition(Vector(horizontalPos,topPos));
    bottomPipe->setPosition(Vector(horizontalPos,bottomPos));
    
    
}

void GamePlayScreenState::update(){
    if(ConstVariables::gameOver==true){
        SoundManager::soundManager.playSound("fly");
        if(ConstVariables::currentScore/2>ConstVariables::highScore){
            ConstVariables::highScore=ConstVariables::currentScore/2;
        }
        
        GlobalGameState::gameStateMachine.pushState(new GameOverScreen());
        
       
    }
    
    //update our delta time
    Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
    dt = timeDiff / 1000.0;
    lastUpdate = SDL_GetTicks();
    
    //TODO DEAL WITH USER INPUT
    //DEAL WITH USER INPUT
    //we check what kind of user input events have happened since our last check
    SDL_Event e;
    //loops through all events and temporarily stores event details in an SDL_Event object
    while (SDL_PollEvent(&e))
    {
        //check if user has clicked on the close window button
        if (e.type == SDL_QUIT) {
            //exit our loop,
            //loop = false;
            GlobalGameState::quitGame = true;
            GlobalGameState::gameStateMachine.popState(); //which will kill this screen
            return;
        }
        //check if user has 'pressed' a button(not held)
        if (e.type == SDL_KEYDOWN) {
            //see if ESC key was pressed
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                //exit loop
                //loop = false;
                GlobalGameState::gameStateMachine.popState(); //which will kill this screen
                return;
            }
            
        }
        
            keyboardHandler.update(&e);
        
      
    }
    //hero->update(dt);
    for (auto e : entities) {
        e->update(dt);
    }
}
void GamePlayScreenState::render(){
    SDL_SetRenderDrawColor(GlobalGameState::renderer, 179, 236, 255, 1);
    
    SDL_RenderClear(GlobalGameState::renderer);
    
    for (auto e : entities) {
        e->draw();
    }
    //hero->draw();
    
    SDL_RenderPresent(GlobalGameState::renderer);
}
bool GamePlayScreenState::onEnter(){
    cout << "Enter Gameplay state" << endl;
    return true;
}
bool GamePlayScreenState::onExit(){
    cout << "Exit Gameplay state" << endl;
    return true;
}
