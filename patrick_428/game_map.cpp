// Our Final Project!!!
// Patrick Schurr, Isaiah LeBlanc, Ben Kennel, Chris Olsen
//Using SDL, SDL_image, standard IO, strings, and file streams


#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "LTexture.h"
#include "Tile.h"
#include "character.h"
#include "knight.h"
#include "mage.h"
#include "archer.h"
#include <vector>
#include <cmath>

//Starts up SDL and creates window
bool init();

std::vector<Tile> mapVec;
//void renderMap(vector<Tile> map);
std::vector<Character *> charVec;
std::vector<Character *> enemyVec;
std::vector<Character *> totalVec;
//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//Sets tiles from tile map
bool setTiles();

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//font
	TTF_Font *gFont = NULL;
	SDL_Rect gSpriteClips[ 4 ];
	LTexture gSpriteSheetTexture;
	//Scene textures
	LTexture gTextTexture;
	LTexture gTileTexture;
	SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
        //Start up SDL and create window
        if( !init() )
        {
                printf( "Failed to initialize!\n" );
        }
	else
	{
		//The level tiles
                Tile* tileSet[ TOTAL_TILES ];

                //Load media
                if( !loadMedia() )
                {
                        printf( "Failed to load media!\n" );
                }
                else
                {
                        //Main loop flag
                        bool quit = false;
                        //Event handler
                        SDL_Event e;
                        int xpos=0;
                        int ypos=0;



			Character* c1=new Archer("brock",12*32,64,true);
                        Character* c2=new Mage("marry",14*32,64,true);
                        Character* c3=new Knight("john",16*32,64,true);
                        Character* c4=new Knight("misty",18*32, 64, true);
                        Character* c5=new Mage("lance", 640, 64, true);
                        Character* c6=new Archer("archer", 22*32, 64, true);
                        charVec.push_back(c1);
                        charVec.push_back(c2);
                        charVec.push_back(c3);
                        charVec.push_back(c4);
                        charVec.push_back(c5);
                        charVec.push_back(c6);

                        //Instantiate player 2 characters
                        Character* e1=new Archer("jesse",12*32,28*32,false);
                        Character* e2=new Mage("james",14*32,28*32,false);
                        Character* e3=new Knight("giovanni",16*32, 28*32,false);
                        Character* e4=new Knight("red", 18*32, 28*32, false);
                        Character* e5=new Mage("meowth", 20*32, 28*32, false);
                        Character* e6=new Archer("blue", 22*32, 28*32, false);
                        enemyVec.push_back(e1);
                        enemyVec.push_back(e2);
                        enemyVec.push_back(e3);
                        enemyVec.push_back(e4);
                        enemyVec.push_back(e5);
                        enemyVec.push_back(e6);
			
			//Active character controlled by player
			Character* current = NULL;

			int turns=5; //max number of turns
			int turnCount=0; //current turns used
			int s; //for event handling
			bool playerTurn=true; //true if player 1 turn
                        //While application is running
                        while( !quit )
                        {
                                //Handle events on queue
                                while( SDL_PollEvent( &e ) != 0 )
                                {
                                        //User requests quit
					 if( e.type == SDL_QUIT )
                                        {
                                                quit = true;
                                        }
					//Check characters adjacent to each character to restrict movement
					vector<Character *> temp; //temporary vector to store all characters
					for(int i=0;i<charVec.size();i++){
						bool up=true; //can move in given direction
						bool down=true;
						bool left=true; 
						bool right=true;
						for(int j=0;j<charVec.size();j++){
							if(i!=j)
								temp.push_back(charVec[j]);
								//temp stores all characters other than charVec[i]
						}
						for(int j=0;j<enemyVec.size();j++)
							temp.push_back(enemyVec[j]);
						for(int j=0;j<temp.size();j++){
							int xst=charVec[i]->getX();
							int yst=charVec[i]->getY();
							if(temp[j]->getX()==xst-32 && temp[j]->getY()==yst)
								left=false;
							if(temp[j]->getX()==xst+32 && temp[j]->getY()==yst)
								right=false;
							if(temp[j]->getX()==xst && temp[j]->getY()==yst-32)
								up=false;
							if(temp[j]->getX()==xst && temp[j]->getY()==yst+32)
								down=false;
							
						}
						//Update possible movements for each character
						charVec[i]->setCanMove(up,down,left,right);
						temp.clear();
					} //Repeat for all enemies
                                        for(int i=0;i<enemyVec.size();i++){
                                                bool up=true;
                                                bool down=true;
                                                bool left=true;
                                                bool right=true;
                                                for(int j=0;j<enemyVec.size();j++){
                                                        if(i!=j)
                                                                temp.push_back(enemyVec[j]);
                                                }
                                                for(int j=0;j<charVec.size();j++)
                                                        temp.push_back(charVec[j]);
                                                for(int j=0;j<temp.size();j++){
                                                        int xst=enemyVec[i]->getX();
                                                        int yst=enemyVec[i]->getY();
                                                        if(temp[j]->getX()==xst-32 && temp[j]->getY()==yst)
                                                                left=false;
                                                        if(temp[j]->getX()==xst+32 && temp[j]->getY()==yst)
                                                                right=false;
                                                        if(temp[j]->getX()==xst && temp[j]->getY()==yst-32)
                                                                up=false;
                                                        if(temp[j]->getX()==xst && temp[j]->getY()==yst+32)
                                                                down=false;

                                                }

                                                enemyVec[i]->setCanMove(up,down,left,right);
						temp.clear();
                                        }

					//Update characters in attacking range of each character
					for(int i=0;i<charVec.size();i++){
						int range=charVec[i]->getRange()*32;
						for(int j=0;j<charVec.size();j++){
							if(i!=j)
								temp.push_back(charVec[j]);
						}
						for(int j=0;j<enemyVec.size();j++)
							temp.push_back(enemyVec[j]);
						for(int j=0;j<temp.size();j++){
							int xdiff=temp[j]->getX()-charVec[i]->getX();
							int ydiff=temp[j]->getY()-charVec[i]->getY();
							if(std::abs(xdiff)<range && std::abs(ydiff)<range){
								charVec[i]->addToRange(temp[j]);
							}
						}
						temp.clear();
					}
                                        for(int i=0;i<enemyVec.size();i++){
                                                int range=enemyVec[i]->getRange()*32;
                                                for(int j=0;j<enemyVec.size();j++){
                                                        if(i!=j)
                                                                temp.push_back(enemyVec[j]);
						}
                                                for(int j=0;j<charVec.size();j++)
                                                        temp.push_back(charVec[j]);
                                                for(int j=0;j<temp.size();j++){
                                                         int xdiff=temp[j]->getX()-enemyVec[i]->getX();
                                                        int ydiff=temp[j]->getY()-enemyVec[i]->getY();


							if(std::abs(xdiff)<range && std::abs(ydiff)<range){
                                                                enemyVec[i]->addToRange(temp[j]);
                                                        }
                                                }
                                                temp.clear();
                                        }


					if(playerTurn){
						for(int i=0;i<charVec.size();i++){
							bool validMove=false;
                                                	Character* c=charVec[i];
							s = c-> handleEvent(e);
							if(s==1){
								turnCount++;
								cout<<"turns remaining: "<<turns-turnCount<<endl;
							}else if(s==2){
								//Wait for mouse click
								cout<<"Click on a character"<<endl;
								SDL_Event g;
								int x =0;
								while(x==0){
									SDL_PollEvent(&g);
									if(g.type==SDL_MOUSEBUTTONDOWN){
										int mousex,mousey;
										SDL_GetMouseState(&mousex,&mousey);
										vector<Character *> inRange=c->getCharsInRange();
										Character* target=NULL;
										for(int i=0;i<inRange.size();i++){
											int xloc=inRange[i]->getX();
											int yloc=inRange[i]->getY();
											//cout<< xloc<<", " << yloc <<endl;
											//cout<< mousex<<", "<<mousey<<endl;
											if(mousex-xloc<32 && mousex-xloc>0 && mousey-yloc<32
												&& mousey-yloc>0){ cout<<"Entered"<<endl;
												target=inRange[i];
												break;
											}
										}if(!target==NULL){
										cout<<c->getName()<<" attacks "<<target->getName()<<endl;
										c->attack(target);
										cout<<target->getName()<<"'s remaining health: ";
										cout<<target->getHealth()<<"/"<<target->getMaxHealth()<<endl;
										cout<<"Attack ends"<<endl;
										validMove=true;
										}else{
											cout<<"Invalid attack"<<endl;
										}
										x=1;
									}
								}
								if(validMove)
								turnCount++;
								cout<<"turns remaining: "<<turns-turnCount<<endl;
							}
						}
					}else{
						for(int i=0;i<enemyVec.size();i++){
                                                	bool validMove=false;
							Character* c2=enemyVec[i];
                                                        s = c2-> handleEvent(e);
                                                        if(s==1){
                                                                turnCount++;
                                                                cout<<"turns remaining: "<<turns-turnCount<<endl;
                                                        }else if(s==2){
								//Wait for mouse click
	                                                        cout<<"Click on a character"<<endl;
                                                                SDL_Event h;
                                                                int x =0;
                                                                while(x==0){
                                                                        SDL_PollEvent(&h);
                                                                        if(h.type==SDL_MOUSEBUTTONDOWN){
                                                                                int mousex,mousey;
                                                                                SDL_GetMouseState(&mousex,&mousey);
		                                                                vector<Character *> inRange=c2->getCharsInRange();
                                                                                Character* target=NULL;
                                                                                for(int i=0;i<inRange.size();i++){
                                                                                        int xloc=inRange[i]->getX();
                                                                                        int yloc=inRange[i]->getY();
                                                                                        if(mousex-xloc<32 && mousex-xloc>0 && mousey-yloc<32
                                                                                                && mousey-yloc>0){
                                                                                                target=inRange[i];
                                                                                                break;
                                                                                        }
                                                                                }
										if(!target==NULL){
                                                                                cout<<c2->getName()<<" attacks "<<target->getName()<<endl;
                                                                                c2->attack(target);
                                                                                cout<<target->getName()<<"'s remaining health: ";
                                                                                cout<<target->getHealth()<<"/"<<target->getMaxHealth()<<endl;
                                                                                cout<<"Attack ends"<<endl;
										validMove=true;
										}
										else{
											cout<< "invalid attack"<<endl;
											}
                                                                                x=1;
                                                                        }
                                                                }
								if(validMove==true)
								turnCount++;


								cout<<"turns remaining: "<<turns-turnCount<<endl;

                                                        }

                                                }

					}

                                }

				//Remove killed characters and clear ranges
				for(int i=0;i<charVec.size();i++){
					charVec[i]->clearRange();
					if(!charVec[i]->getIsAlive()){
						cout<<"Is Alive"<<endl;
						charVec.erase(charVec.begin()+i);}
				}
				for(int i=0;i<enemyVec.size();i++){
					enemyVec[i]->clearRange();
					if(!enemyVec[i]->getIsAlive())
						enemyVec.erase(enemyVec.begin()+i);
				}
				//Switch player turn
				if(turns<=turnCount){
					cout<<"Out of turns"<<endl;
					turnCount=0;
					playerTurn=!playerTurn;
					//Unset active character
					for(int i=0;i<charVec.size();i++)
						charVec[i]->setOnMe(false);
					for(int i=0;i<enemyVec.size();i++)
						enemyVec[i]->setOnMe(false);
				}
				//Determine if game has ended
				if(charVec.size()==0){
					cout<<"Player 2 wins!"<<endl;
					quit=true;
				}else if(enemyVec.size()==0){
					cout<<"Player 1 wins!"<<endl;
					quit=true;
				}
				
                                //Clear screen
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                
				for(std::vector<Tile>::iterator it = mapVec.begin(); it!=mapVec.end(); ++it){
                                Tile temp=*it;
				temp.render();
                                }

				  for(int i=0; i<charVec.size();i++)
				     {
       					charVec[i]->render();
					 }
				for(int i=0;i<enemyVec.size();i++){
					enemyVec[i]->render();
				}

                                gSpriteSheetTexture.render(xpos,ypos, &gSpriteClips[0]);      
                                // render text box
                                 gTextTexture.render(5,500);

                                //Update screen
                                SDL_RenderPresent( gRenderer );
                        }
                }
                //Free resources and close SDL
                close();
        }

	return 0;
}




bool init()
{
	SDL_Window* gWindow = NULL;

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Fire Emblem - Classroom Style", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if(TTF_Init() == -1)
                                {
                                        printf("SDL_ttf could not be initialized! SDL_ttf ERror: %s\n", TTF_GetError());
                                        success = false;
                                }

			}
		}
	}

	return success;
}



bool loadMedia()
{
	//Loading success flag
	bool success = true;

	SDL_Rect gSpriteClips[ 4 ];

	LTexture gSpriteSheetTexture;


	if( !gSpriteSheetTexture.loadFromFile( "animal_crossing.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
	 gSpriteClips[ 0 ].x =   256;
        gSpriteClips[ 0 ].y =   224;
        gSpriteClips[ 0 ].w = 32;
        gSpriteClips[ 0 ].h = 32;

  	gSpriteClips[ 1 ].x = 100;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 100;
        gSpriteClips[ 1 ].h = 100;

	  gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 100;
        gSpriteClips[ 2 ].w = 100;
        gSpriteClips[ 2 ].h = 100;

	   gSpriteClips[ 3 ].x = 100;
        gSpriteClips[ 3 ].y = 100;
        gSpriteClips[ 3 ].w = 100;
        gSpriteClips[ 3 ].h = 100;
	//printf("Loaded spritesheet!");
	    }

	//Load tile texture
	if( !gTileTexture.loadFromFile( "animal_crossing.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles() )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}
	gFont = TTF_OpenFont( "game_over.ttf", 50 );
                if( gFont == NULL )
                {
                 printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
                }
                 else {

                         SDL_Color textColor = { 0, 0, 0};
                         SDL_Color backColor = {255,255,255};
                         if( !gTextTexture.loadFromRenderedText( "OUR GAME", textColor, backColor ) )
                                 {
                                        printf( "Failed to render text texture!\n" );
                                                success = false;
                                                 }
                        }

	return success;
}

void close()
{
	SDL_Window* gWindow = NULL;

	//Free loaded images
	gTileTexture.free();
	gTextTexture.free();
	//Destroy window	
	  TTF_CloseFont(gFont);
        gFont = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

bool setTiles()
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "finalmap.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				mapVec.push_back(Tile( x, y, tileType ));
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_WATER].x = 0;
			gTileClips[ TILE_WATER ].y = 288;
			gTileClips[ TILE_WATER ].w = TILE_WIDTH;
			gTileClips[ TILE_WATER ].h = TILE_HEIGHT;

			gTileClips[ TILE_ROCK ].x = 190;
			gTileClips[ TILE_ROCK ].y = 0;
			gTileClips[ TILE_ROCK ].w = TILE_WIDTH;
			gTileClips[ TILE_ROCK ].h = TILE_HEIGHT;

			gTileClips[ TILE_GRASS ].x = 0;
			gTileClips[ TILE_GRASS].y = 0;
			gTileClips[ TILE_GRASS].w = TILE_WIDTH;
			gTileClips[ TILE_GRASS].h = TILE_HEIGHT;

			gTileClips[ TILE_SAND ].x = 64;
			gTileClips[ TILE_SAND ].y = 32;
			gTileClips[ TILE_SAND ].w = TILE_WIDTH;
			gTileClips[ TILE_SAND ].h = TILE_HEIGHT;
		
			gTileClips[ TILE_GUESS ].x = 224;
                        gTileClips[ TILE_GUESS ].y = 224;
                        gTileClips[ TILE_GUESS ].w = TILE_WIDTH;
                        gTileClips[ TILE_GUESS ].h = TILE_HEIGHT;
		}
	}
	

	if(!kCharTexture.loadFromFile("knight.png")){
		printf("Failed to load");
	}
	
        kTileClips[0].x=0;
        kTileClips[0].y=0;
        kTileClips[0].w=32;
        kTileClips[0].h=32;
	
	  if(!aCharTexture.loadFromFile("archer.png")){
                printf("Failed to load");
	}

	
        aTileClips[0].x=0;
        aTileClips[0].y=0;
        aTileClips[0].w=32;
        aTileClips[0].h=32;
	 

	 if(!mCharTexture.loadFromFile("mage.png")){
                printf("Failed to load");
	}

        mTileClips[0].x=0;
        mTileClips[0].y=0;
        mTileClips[0].w=32;
        mTileClips[0].h=32;

	if(!kEnCharTexture.loadFromFile("knight_en.png")){
		printf("Failed to load");
	}
	
        kEnTileClips[0].x=0;
        kEnTileClips[0].y=0;
        kEnTileClips[0].w=30;
        kEnTileClips[0].h=33;
	
	  if(!aEnCharTexture.loadFromFile("archer_en.png")){
                printf("Failed to load");
	}

	
        aEnTileClips[0].x=0;
        aEnTileClips[0].y=0;
        aEnTileClips[0].w=30;
        aEnTileClips[0].h=35;
	 

	 if(!mEnCharTexture.loadFromFile("mage_en.png")){
                printf("Failed to load");
	}

        mEnTileClips[0].x=0;
        mEnTileClips[0].y=0;
        mEnTileClips[0].w=36;
        mEnTileClips[0].h=38;



	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}
