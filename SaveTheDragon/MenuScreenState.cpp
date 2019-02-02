#include "MenuScreenState.hpp"


MenuScreenState::MenuScreenState()
{
    ConstVariables::gameOver=false;
    ConstVariables::currentScore=0;
    
    SDL_SetRenderDrawColor(GlobalGameState::renderer, 173, 0, 0, 255);
    SDL_RenderClear(GlobalGameState::renderer);
    
    TTF_Font* font;
    font= TTF_OpenFont("Halo3.ttf", 70);
    
    SDL_Color textColor = {6, 50, 0,33};
    
    
    
    
    //Displaying text

    
    int topx=150,topy=30;
    DrawText* text1 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"Save The Dragon", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text1->textTexture = textTexture;
    entities.push_back(text1);
    
    
    
    SDL_Surface* runSurface = IMG_Load("newDragon.png");
    //tell surface which colour should be invisible
    //SDL_SetColorKey(runSurface, 1, SDL_MapRGB(runSurface->format, 128, 128, 255));
    //convert it to texture
    heroTexture = SDL_CreateTextureFromSurface(GlobalGameState::renderer, runSurface);
    //cleanup surface memory
    SDL_FreeSurface(runSurface);
    
    heroAnimation = new Animation(heroTexture, GlobalGameState::renderer,8, 129, 128, 0.085);
   
    hero = new Hero();
    hero->setAnimation(heroAnimation);
    hero->setRenderer(GlobalGameState::renderer);
    hero->pos.x = topx+300;
    hero->pos.y = topy+100;
    
    entities.push_back(hero);
    
    
    font= TTF_OpenFont("Halo3.ttf", 50);

    topx= topx+180;
    topy=topy+220;
    DrawText* text4 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"High Score", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text4->textTexture = textTexture;
    entities.push_back(text4);
    
    

    
    
    
    
    font= TTF_OpenFont("Halo3.ttf", 90);
    
    topx= topx+50;
    topy=topy+50;
    DrawText* text5 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,to_string(ConstVariables::highScore).c_str(), textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text5->textTexture = textTexture;
    entities.push_back(text5);
    
    font= TTF_OpenFont("Halo3.ttf", 25);
    topx= topx-150;
    topy=topy+160;
    DrawText* text2 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"Press SPACE To Start The Game", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text2->textTexture = textTexture;
    entities.push_back(text2);
    
     topx= topx+200;
    topy=topy+50;
    DrawText* orText = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"OR", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    orText->textTexture = textTexture;
    entities.push_back(orText);
    
    topx= topx-170;
    topy=topy+50;
    DrawText* text3 = new DrawText(topx,topy);
    textSurface = TTF_RenderText_Blended(font,"Press ESC To Quit The Game", textColor);
    textTexture =SDL_CreateTextureFromSurface(GlobalGameState::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    text3->textTexture = textTexture;
    entities.push_back(text3);
    
}


MenuScreenState::~MenuScreenState()
{
    TTF_CloseFont(font);
    delete hero;
    
    delete heroAnimation;
    SDL_DestroyTexture(textTexture);

    SDL_DestroyTexture(heroTexture);
}

void MenuScreenState::update(){
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
				GlobalGameState::gameStateMachine.pushState(new GamePlayScreenState());
			}
		}
	}
    for (auto e : entities) {
        e->update(0);
    }
}
void MenuScreenState::render(){
    SDL_SetRenderDrawColor(GlobalGameState::renderer, 179, 236, 255, 1);
    
    SDL_RenderClear(GlobalGameState::renderer);
    
    for (auto e : entities) {
        e->draw();
    }
    //hero->draw();
    
    SDL_RenderPresent(GlobalGameState::renderer);
}
bool MenuScreenState::onEnter(){
	std::cout << "Entering menu state" << std::endl;
	return true;
}
bool MenuScreenState::onExit(){
	std::cout << "Exiting menu state" << std::endl;
	return true;
}
