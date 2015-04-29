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
/*
//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

//The dimensions of the level
const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 800;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES =1250;
const int TOTAL_TILE_SPRITES = 5;

//The different tile sprites
const int TILE_WATER = 0;
const int TILE_ROCK = 1;
const int TILE_GRASS = 2;
const int TILE_SAND = 3;
const int TILE_GUESS = 4;
*/
//Starts up SDL and creates window
bool init();

std::vector<Tile> mapVec;
//void renderMap(vector<Tile> map);
std::vector<Character *> charVec;
std::vector<Character *> enemyVec;
//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//Sets tiles from tile map
bool setTiles();
/*
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


//font
TTF_Font *gFont = NULL;
SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;
//Scene textures
LTexture gTextTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
*/

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	//SDL_Renderer* gRenderer = NULL;


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
                        int ypos = 0;

			Character* c1=new Knight("brock",32,32,false);
                        Character* c2=new Knight("marry",64,64,false);
                        Character* c3=new Knight("john",96,96,false);
                        charVec.push_back(c1);
                        charVec.push_back(c2);
                        charVec.push_back(c3);

			Character* e1=new Knight("enemy1",15*32,12*32,true);
			Character* e2=new Knight("enemy2",14*32,10*32,true);
			enemyVec.push_back(e1);
			enemyVec.push_back(e2);
			
			Character* current = NULL;
                        //Level camera
                        //SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


			int turns=5;
			int turnCount=0;
			int s;
			bool playerTurn=true;
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
					if(playerTurn){    
						for(int i=0;i<charVec.size();i++){
                                                	Character* c=charVec[i];
							s = c-> handleEvent(e);
							if(s==1){
								turnCount++;
								cout<<"turn used"<<endl;
							}
						}
					}else{
						for(int i=0;i<enemyVec.size();i++){
                                                	Character* c=enemyVec[i];
                                                        s = c-> handleEvent(e);
                                                        if(s==1){
                                                                turnCount++;
                                                                cout<<"turn used"<<endl;
                                                        }
                                                }

					}
                                        /*if(e.type==SDL_MOUSEBUTTONDOWN){
                                        	int x,y;
                                        	SDL_GetMouseState(&x,&y);
						for(int i=0;i<charVec.size();i++){
							Character* c=charVec[i];
							xpos=c->getX()*TILE_WIDTH;
							ypos=c->getY()*TILE_HEIGHT;
                                        		if((x>xpos)&&(x<xpos+32)&&(y>ypos)&&(y<ypos+32)){
								current=c;
								cout<<"Current character changed"<<endl;
                                        		}
                                        	}
					}
                                        if(current != NULL && e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){
                                        	current->moveUp(32);
						cout<<"Move up"<<endl;
						ypos-=32;
                                        }
                                        if(current != NULL && e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
						current->moveDown(32);
						cout<<"Move right"<<endl;
                                        	xpos+=32;
                                        }
                                        if(current != NULL && e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN){
                                        	current->moveLeft(32);
						cout<<"Move down"<<endl;
						ypos+=32;
                                        }
                                        if(current != NULL && e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){
                                        	current->moveRight(32);
						cout<<"Move left"<<endl;
						xpos-=32;
                                        }*/

                                }
				if(turns<=turnCount){
					cout<<"Out of turns"<<endl;
					turnCount=0;
					playerTurn=!playerTurn;
					for(int i=0;i<charVec.size();i++)
						charVec[i]->setOnMe(false);
					for(int i=0;i<enemyVec.size();i++)
						enemyVec[i]->setOnMe(false);
				}
                                //Clear screen
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                
				for(std::vector<Tile>::iterator it = mapVec.begin(); it!=mapVec.end(); ++it){
                                Tile temp=*it;
				temp.render();
                                }
				 /*for(std::vector<Character>::iterator it = charVec.begin(); it!=charVec.end(); ++it){
				*it->render();
				}*/

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


	if( !gSpriteSheetTexture.loadFromFile( "spritesheet.png" ) )
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
	if( !gTileTexture.loadFromFile( "spritesheet.png" ) )
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

			gTileClips[ TILE_ROCK ].x = 0;
			gTileClips[ TILE_ROCK ].y = 32;
			gTileClips[ TILE_ROCK ].w = TILE_WIDTH;
			gTileClips[ TILE_ROCK ].h = TILE_HEIGHT;

			gTileClips[ TILE_GRASS ].x = 32;
			gTileClips[ TILE_GRASS].y = 288;
			gTileClips[ TILE_GRASS].w = TILE_WIDTH;
			gTileClips[ TILE_GRASS].h = TILE_HEIGHT;

			gTileClips[ TILE_SAND ].x = 320;
			gTileClips[ TILE_SAND ].y = 416;
			gTileClips[ TILE_SAND ].w = TILE_WIDTH;
			gTileClips[ TILE_SAND ].h = TILE_HEIGHT;
		
			gTileClips[ TILE_GUESS ].x = 0;
                        gTileClips[ TILE_GUESS ].y = 272;
                        gTileClips[ TILE_GUESS ].w = TILE_WIDTH;
                        gTileClips[ TILE_GUESS ].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}
/*
int main( int argc, char* args[] )
{
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


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
		if( !loadMedia( tileSet ) )
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
			int ypos = 0;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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
					if(e.type==SDL_MOUSEBUTTONDOWN){
					int x,y;
					SDL_GetMouseState(&x,&y);
					if((x>xpos)&&(x<xpos+32)&&(y>ypos)&&(y<ypos+32)){
					xpos+=32;
					ypos+=32;
					}
					}
					if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){
					ypos-=32;
					}
					if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
					xpos+=32;
					}
					if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN){
					ypos+=32;
					}
					if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){
					xpos-=32;
					}


				}



				
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				

				
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}
				
				//gSpriteSheetTexture.renderSprite( 0, 0, &gSpriteClips[ 0 ] );

				gSpriteSheetTexture.render(xpos,ypos, &gSpriteClips[0]);	
				
				// render text box
				 gTextTexture.render(5,500);


				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
		
		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}*/

