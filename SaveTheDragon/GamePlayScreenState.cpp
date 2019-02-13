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
    hero->pos.y = 200;//200
    
    entities.push_back(hero);
  
    keyboardHandler.hero = hero;
    
   pipeImage = SDL_LoadBMP("pipes.bmp");
     pipeTexture = SDL_CreateTextureFromSurface(GlobalGameState::renderer, pipeImage);
    //creating the floors and add them to entities
    
    
    
    int horizontalPos=1000;
    
    //initializing random number
    srand((unsigned int)time(NULL));
    for(int i=0;i<1000;i++){
        
        
        
        horizontalPos = horizontalPos+ ConstVariables::PIPE_HORIZONTAL_SPACING;
        Pipes* topPipe = new Pipes(50,600);
        topPipe->pipeTop=true;
        topPipe->texture = pipeTexture;
        topPipe->setRenderer(GlobalGameState::renderer);
        //topPipe->setPosition(Vector(horizontalPos,0));
        topPipe->velocity.x=ConstVariables::PIPE_VElOCITY;
        
        entities.push_back(topPipe);
        
        //floor
        /**/
        
        
        Pipes* bottomPipe = new Pipes(50,600);
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
    
    font= TTF_OpenFont("Games.ttf", 20);
    
    textColor = {6, 50, 0,33};
    
    //displaying control options to user
    DrawText* userGuideText = new DrawText(400,200);
    textSurface = TTF_RenderText_Blended(font, "Press Space To FLY", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    userGuideText->textTexture = textTexture;
    userGuideText->velocity.x=200;
    pointsEntity.push_back(userGuideText);
    
    //floors for left side of the screen
    //dragon can't collide with this one
    Pipes* floor2 = new Pipes(205,200);
    floor2->texture = pipeTexture;
    
    floor2->setRenderer(GlobalGameState::renderer);
    floor2->setPosition(Vector(-5,ConstVariables::WIN_HEIGHT-46));
    pointsEntity.push_back(floor2);
    
    
    
  
    
    
    
  

    
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
    while(!(verticalSpacing==ConstVariables::MIN_VERTICAL_SPACING)){//TODO
        topPos = rand()% 450 +(-450);
        bottomPos = rand()% ((600-200)+1)+200;
        verticalSpacing = (-topPos)+bottomPos;
        
    }
    topPipe->setPosition(Vector(horizontalPos,topPos));
    bottomPipe->setPosition(Vector(horizontalPos,bottomPos));
    
    
}

void GamePlayScreenState::update(){

    if(pointsEntity.size()>2){
        
   pointsEntity.erase(pointsEntity.begin());
    }
    
    
    if(ConstVariables::POINT_SCORED){
       
        
        
        
        
        //Displaying text
        font= TTF_OpenFont("Games.ttf", 90);

        DrawText* text1 = new DrawText(50,40);
        textSurface = TTF_RenderText_Blended(font,to_string(ConstVariables::currentScore/2).c_str(), textColor);
        textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
        SDL_FreeSurface(textSurface);
       
        text1->textTexture = textTexture;
        pointsEntity.push_back(text1);
        Pipes* floor2 = new Pipes(205,200);
        floor2->texture = pipeTexture;
        
        floor2->setRenderer(GlobalGameState::renderer);
        floor2->setPosition(Vector(-5,ConstVariables::WIN_HEIGHT-46));
        pointsEntity.push_back(floor2);
        ConstVariables::POINT_SCORED=false;
      
   }
    if(ConstVariables::gameOver==true){
        SoundManager::soundManager.playSound("die");
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
    for (auto e : pointsEntity) {
        e->update(dt);
    }
}
void GamePlayScreenState::render(){
    SDL_SetRenderDrawColor(GlobalGameState::renderer, 179, 236, 255, 1);
    
    SDL_RenderClear(GlobalGameState::renderer);
    
    for (auto e : entities) {
        e->draw();
    }
    for (auto e : pointsEntity) {
        e->draw();
    }
    //hero->draw();
    
    SDL_RenderPresent(GlobalGameState::renderer);
}
bool GamePlayScreenState::onEnter(){
    return true;
}
bool GamePlayScreenState::onExit(){
    return true;
}
