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
                        int ypos = 0;

			Character* c1=new Knight("brock",32,32,false);
                        Character* c2=new Knight("marry",64,64,false);
                        Character* c3=new Archer("john",96,96,false);
                        charVec.push_back(c1);
                        charVec.push_back(c2);
                        charVec.push_back(c3);

			Character* e1=new Knight("enemy1",15*32,12*32,true);
			Character* e2=new Archer("enemy2",14*32,10*32,true);
			Character * e3=new Mage("enemy3",13*32, 20*32,true);


			enemyVec.push_back(e1);
			enemyVec.push_back(e2);
			enemyVec.push_back(e3);
			for(int i=0;i<charVec.size();i++)
				totalVec.push_back(charVec[i]);
			for(int i=0;i<enemyVec.size();i++)
				totalVec.push_back(enemyVec[i]);
			
			Character* current = NULL;


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
					//Check characters in range
					vector<Character *> temp;
					for(int i=0;i<charVec.size();i++){
						bool up=true;
						bool down=true;
						bool left=true;
						bool right=true;
						for(int j=0;j<charVec.size();j++){
							if(i!=j)
								temp.push_back(charVec[j]);
								//Temp stores all characters other than charVec[i]
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
						
						charVec[i]->setCanMove(up,down,left,right);
						temp.clear();
					}
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

					
						/*for(int j=i+1;j<charVec.size();j++){
							int xdiff=charVec[i]->getX()-temp[j]->getX();
							int ydiff=charVec[i]->getY()-temp[j]->getY();
							if((xdiff<64 && xdiff>-64) && (ydiff<64 && ydiff>-64)){
								if(ydiff>0){
									up=false;
									down2=false;
								}else if(ydiff<0){
									down=false;
									up2=false;
								}else if(xdiff>0){
									left=false;
									right2=false;
								}else if(xdiff<0){
									right=false;
									left2=false;
								}
							}

							for(int k=0;k<charVec.size();k++)
								if(charVec[k]==totalVec[i]){
									charVec[k]->setCanMove(up,down,left,right);
								}
							for(int k=0;k<enemyVec.size();k++)
								if(enemyVec[k]==totalVec[i]){
									enemyVec[k]->setCanMove(up,down,left,right);
								}*/
							//totalVec[j]->setCanMove(up,down,left,right);
							//charVec[j]->setCanMove(up2,down2,left2,right2);
						//}
                                                /*for(int j=i+1;j<enemyVec.size();j++){
                                                        int xdiff=enemyVec[i]->getX()-enemyVec[j]->getX();
                                                        int ydiff=enemyVec[i]->getY()-enemyVec[j]->getY();
                                                        if((xdiff<64 && xdiff>-64) && (ydiff<64 && ydiff>-64)){
                                                                if(ydiff>0){
                                                                        up=false;
                                                                        down2=false;
                                                                }else if(ydiff<0){
                                                                        down=false;
                                                                        up2=false;
                                                                }else if(xdiff>0){
                                                                        left=false;
                                                                        right2=false;
                                                                }else if(xdiff<0){
                                                                        right=false;
                                                                        left2=false;
                                                                }
                                                        }
                                                        enemyVec[j]->setCanMove(up2,down2,left2,right2);
                                                }*/

						
						//charVec[i]->setCanMove(up,down,left,right);
					//}
                                        /*for(int i=0;i<charVec.size()-1;i++){
                                                bool up=true;
                                                bool down=true;
                                                bool left=true;
                                                bool right=true;
                                                bool up2=true;
                                                bool down2=true;
                                                bool left2=true;
                                                bool right2=true;

                                                for(int j=i+1;j<enemyVec.size();j++){
                                                        int xdiff=charVec[i]->getX()-enemyVec[j]->getX();
                                                        int ydiff=charVec[i]->getY()-enemyVec[j]->getY();
                                                        if((xdiff<64 && xdiff>-64) && (ydiff<64 && ydiff>-64)){
                                                                if(ydiff>0){
                                                                        up=false;
                                                                        down2=false;
                                                                }else if(ydiff<0){
                                                                        down=false;
                                                                        up2=false;
                                                                }else if(xdiff>0){
                                                                        left=false;
                                                                        right2=false;
                                                                }else if(xdiff<0){
                                                                        right=false;
                                                                        left2=false;
                                                                }
                                                        }
                                                        enemyVec[j]->setCanMove(up2,down2,left2,right2);
                                                }
                                                charVec[i]->setCanMove(up,down,left,right);
                                        }*/
                                        /*for(int i=0;i<enemyVec.size()-1;i++){
                                                bool up=true;
                                                bool down=true;
                                                bool left=true;
                                                bool right=true;
                                                bool up2=true;
                                                bool down2=true;
                                                bool left2=true;
                                                bool right2=true;

                                                for(int j=i+1;j<enemyVec.size();j++){
                                                        int xdiff=enemyVec[i]->getX()-enemyVec[j]->getX();
                                                        int ydiff=enemyVec[i]->getY()-enemyVec[j]->getY();
                                                        if((xdiff<64 && xdiff>-64) && (ydiff<64 && ydiff>-64)){
                                                                if(ydiff>0){
                                                                        up=false;
                                                                        down2=false;
                                                                }else if(ydiff<0){
                                                                        down=false;
                                                                        up2=false;
                                                                }else if(xdiff>0){
                                                                        left=false;
                                                                        right2=false;
                                                                }else if(xdiff<0){
                                                                        right=false;
                                                                        left2=false;
                                                                }
                                                        }
                                                        enemyVec[j]->setCanMove(up2,down2,left2,right2);
						}
                                                for(int j=i+1;j<charVec.size();j++){
                                                        int xdiff=charVec[i]->getX()-charVec[j]->getX();
                                                        int ydiff=charVec[i]->getY()-charVec[j]->getY();
                                                        if((xdiff<64 && xdiff>-64) && (ydiff<64 && ydiff>-64)){
                                                                if(ydiff>0){
                                                                        up=false;
                                                                        down2=false;
                                                                }else if(ydiff<0){
                                                                        down=false;
                                                                        up2=false;
                                                                }else if(xdiff>0){
                                                                        left=false;
                                                                        right2=false;
                                                                }else if(xdiff<0){
                                                                        right=false;
                                                                        left2=false;
                                                                }
                                                        }
                                                        charVec[j]->setCanMove(up2,down2,left2,right2);

                                                }
                                                enemyVec[i]->setCanMove(up,down,left,right);
                                        }*/

					//Update characters in range
					for(int i=0;i<charVec.size();i++){
						int range=charVec[i]->getRange()*32;
						for(int j=0;j<charVec.size();j++){
							if(i!=j)
								temp.push_back(charVec[j]);
						}
						for(int j=0;j<enemyVec.size();j++)
							temp.push_back(enemyVec[j]);
						for(int j=0;j<temp.size();j++){
							int xdiff=range-temp[j]->getX();
							int ydiff=range-temp[j]->getY();
							if(std::abs(xdiff)<range && std::abs(ydiff)<range){
								cout<<"Character in range"<<endl;
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
                                                        int xdiff=range-temp[j]->getX();
                                                        int ydiff=range-temp[j]->getY();
                                                        if(std::abs(xdiff)<range && std::abs(ydiff)<range){
                                                                cout<<"Character in range"<<endl;
                                                                charVec[i]->addToRange(temp[j]);
                                                        }
                                                }
                                                temp.clear();
                                        }


					if(playerTurn){
						for(int i=0;i<charVec.size();i++){
                                                	Character* c=charVec[i];
							if(e.key.keysym.sym==SDLK_SPACE){
								cout<<"Click on a character"<<endl;
								int mousex, mousey;
								
							}
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
	

	if(!gCharTexture.loadFromFile("charSprites.png")){
		printf("Failed to load");
}
        cTileClips[0].x=0;
        cTileClips[0].y=0;
        cTileClips[0].w=32;
        cTileClips[0].h=32;

	cTileClips[1].x=32;
        cTileClips[1].y=0;
        cTileClips[1].w=32;
        cTileClips[1].h=32;

	cTileClips[2].x=64;
        cTileClips[2].y=0;
        cTileClips[2].w=32;
        cTileClips[2].h=32;

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}
