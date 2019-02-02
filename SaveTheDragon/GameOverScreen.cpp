//
//  GameOverScreen.cpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 2/2/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

#include "GameOverScreen.hpp"

GameOverScreen::GameOverScreen()
{
    SDL_SetRenderDrawColor(GlobalGameState::renderer, 173, 0, 0, 255);
    SDL_RenderClear(GlobalGameState::renderer);
    
    TTF_Font* font;
    font= TTF_OpenFont("Halo3.ttf", 90);
    
    SDL_Color textColor = {6, 50, 0,33};
    
    
    
    
    //Displaying text
    
    
    int topx=225,topy=100;
    DrawText* text1 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"GameOver", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text1->textTexture = textTexture;
    entities.push_back(text1);
    
    
 
    
    
    font= TTF_OpenFont("Halo3.ttf", 50);
    
    topx= topx+100;
    topy=topy+220;
    DrawText* text4 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"Your Score", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text4->textTexture = textTexture;
    entities.push_back(text4);
    
    topy=topy+50;
    string as="";
    DrawText* text5 = new DrawText(topx+100,topy);
    textSurface = TTF_RenderText_Blended(font,to_string(ConstVariables::currentScore/2).c_str(), textColor);//converting the integer currentScore to string 
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text5->textTexture = textTexture;
    entities.push_back(text5);
    
    
    
   
    topy=topy+100;
    DrawText* highText = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"High Score", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    highText->textTexture = textTexture;
    entities.push_back(highText);
    
    topy=topy+50;
    DrawText* highScoreText = new DrawText(topx+100,topy);
    textSurface = TTF_RenderText_Blended(font,to_string(ConstVariables::highScore).c_str(), textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    highScoreText->textTexture = textTexture;
    entities.push_back(highScoreText);
    
    
}


GameOverScreen::~GameOverScreen()
{
    TTF_CloseFont(font);

    SDL_DestroyTexture(textTexture);
   
}

void GameOverScreen::update(){
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){
            //exit our loop,
            GlobalGameState::quitGame = true;
            GlobalGameState::gameStateMachine.popState(); //which will kill this screen
            return;
            
        }
        if (e.type == SDL_KEYDOWN){
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                //exit loop
                GlobalGameState::quitGame = true;
                GlobalGameState::gameStateMachine.popState(); //which will kill this screen
                return;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE){
                //start the game!
                GlobalGameState::gameStateMachine.pushState(new MenuScreenState());
            }
        }
    }
    for (auto e : entities) {
        e->update(0);
    }
}
void GameOverScreen::render(){
    SDL_SetRenderDrawColor(GlobalGameState::renderer, 179, 236, 255, 1);
    
    SDL_RenderClear(GlobalGameState::renderer);
    
    for (auto e : entities) {
        e->draw();
    }
    //hero->draw();
    
    SDL_RenderPresent(GlobalGameState::renderer);
}
bool GameOverScreen::onEnter(){
    std::cout << "Entering menu state" << std::endl;
    return true;
}
bool GameOverScreen::onExit(){
    std::cout << "Exiting menu state" << std::endl;
    return true;
}
