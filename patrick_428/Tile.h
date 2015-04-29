//Tile.h
#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<vector>
//Screen dimension constants
const int SCREEN_WIDTH = 1152; //600;
const int SCREEN_HEIGHT = 960; //600;

//The dimensions of the level
const int LEVEL_WIDTH = 1152;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES =1080;
const int TOTAL_TILE_SPRITES = 5;

//The different tile sprites
const int TILE_WATER = 0;
const int TILE_ROCK = 1;
const int TILE_GRASS = 2;
const int TILE_SAND = 3;
const int TILE_GUESS = 4;


//Scene textures
LTexture gCharTexture;
LTexture gFontTexture;
LTexture gTextTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
SDL_Rect cTileClips[3];

class Tile
{
    public:
                Tile();

		//Initializes position and type
                Tile( int x, int y, int tileType );

                //Shows the tile
                void render();
		void renderChar();
		void set_xpos(int);
		void set_ypos(int);
		void set_type(int);

                //Get the tile type
                int getType();

                //Get the collision box
                SDL_Rect getBox();

    private:
                //The attributes of the tile
                SDL_Rect mBox;

                //The tile type
                int mType;
};


Tile::Tile(){
mBox.x=0;
mBox.y=0;
    //Set the collision box
       mBox.w = TILE_WIDTH;
        mBox.h = TILE_HEIGHT;
   
     //Get the tile type
        mType =0;
         }
    
Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

void Tile::render()
{
        gTileTexture.render( mBox.x, mBox.y, &gTileClips[ mType ] );
}


void Tile::renderChar()
{
gCharTexture.render(mBox.x, mBox.y, &cTileClips[mType]);
}


int Tile::getType()
{
    return mType;
}

void Tile::set_xpos(int myX)
{
mBox.x= myX;
}
void Tile::set_ypos(int myY)
{
mBox.y = myY;
}
void Tile:: set_type(int new_Type)
{
mType=new_Type;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
#endif
