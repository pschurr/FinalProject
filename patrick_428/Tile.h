//Tile.h
#ifndef TILE_H
#define TILE_H
#include<iostream>
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
LTexture kCharTexture;

LTexture kEnCharTexture;
LTexture aCharTexture;
LTexture aEnCharTexture;

LTexture mCharTexture;
LTexture mEnCharTexture;

LTexture gFontTexture;
LTexture gTextTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
SDL_Rect kTileClips[1];

SDL_Rect aTileClips[1];

SDL_Rect mTileClips[1];
SDL_Rect mEnTileClips[1];
SDL_Rect aEnTileClips[1];
SDL_Rect kEnTileClips[1];


class Tile
{
    public:
                Tile();

		//Initializes position and type
                Tile( int x, int y, int tileType );

                //Shows the tile
                void render();
		void renderArcher(bool);
		void renderKnight(bool);
		void renderMage(bool);
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


void Tile::renderKnight(bool isEne)
{
if(!isEne){
kCharTexture.render(mBox.x, mBox.y, &kTileClips[0]);
}
else{
kEnCharTexture.render(mBox.x, mBox.y, &kEnTileClips[0]);
std::cout<<"should render enemy"<<std::endl;
}
}
void Tile::renderArcher(bool isEne)
{
if(!isEne)
aCharTexture.render(mBox.x, mBox.y, &aTileClips[0]);
else
aEnCharTexture.render(mBox.x, mBox.y, &aEnTileClips[0]);
}
void Tile::renderMage(bool isEne)
{
if(!isEne)
mCharTexture.render(mBox.x, mBox.y, &mTileClips[0]);
else
mEnCharTexture.render(mBox.x, mBox.y, &mEnTileClips[0]);

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
