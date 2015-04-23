// Our Final Project!!!
// Patrick Schurr, Isaiah LeBlanc, Ben Kennel, Chris Olsen
//Using SDL, SDL_image, standard IO, strings, and file streams


#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

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

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Color backColor );

		//Deallocates texture
		void free();
		

		// rendering characters
		void renderSprite( int x, int y, SDL_Rect* clip = NULL );

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The tile
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

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );


//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

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

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Color backColor )
{
        //Get rid of preexisting texture
                free();
             SDL_Color Black = {0,0,0};
             //Render text surface
         SDL_Surface* textSurface = TTF_RenderText_Shaded( gFont, textureText.c_str(), textColor, backColor);
           if( textSurface != NULL )
                   {
             //Create texture from surface pixels
                  mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        	   if( mTexture == NULL )
                                 {   
                            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());                                                                                                                                }
          else                                                                                                                                    {                                                                                                                      //Get image dimensions
           mWidth = textSurface->w;
         mHeight = textSurface->h;
		}
		 SDL_FreeSurface( textSurface );

		        }
        else
        {
                printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
		// returtn success
		return mTexture != NULL;


}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
//render function for characters

void LTexture::renderSprite( int x, int y, SDL_Rect* clip )
{
    //Set rendering space and render to screen
      SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
          //Set clip rendering dimensions
          if( clip != NULL )
                  {
                          renderQuad.w = clip->w;
                          renderQuad.h = clip->h;
                   }
                                           //Render to screen
                SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
  }


void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
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

bool init()
{
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

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;


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
    }

	//Load tile texture
	if( !gTileTexture.loadFromFile( "spritesheet.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
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

void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] == NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

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

bool setTiles( Tile* tiles[] )
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
				tiles[ i ] = new Tile( x, y, tileType );
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

int main( int argc, char* args[] )
{
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
}

