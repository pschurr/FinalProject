//Tile.h
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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


//Scene textures
LTexture gTextTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];


class Tile
{
    public:
                //Initializes position and type
                Tile( int x, int y, int tileType );

                //Shows the tile
                void render( SDL_Rect& camera );

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

void Tile::render( SDL_Rect& camera )
{
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

