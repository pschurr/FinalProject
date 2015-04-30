//LTexture.h - Texture wrapper class
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
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

//The window renderer
SDL_Renderer* gRenderer = NULL;


//font
TTF_Font *gFont;

class LTexture
{
	public:
		LTexture();
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
std::string file = path.c_str();
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
	if(file=="mage.png"){
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x5A,0x78,0xD4 ) );
		}
	if(file=="mage_en.png"){
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x0A,0x81,0x80 ) );
		}
	
	if(file=="knight.png"){
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00,0x81,0x15 ) );
		}
		
	if(file=="knight_en.png"){
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00,0x81,0x15 ) );
	}

	if(file=="archer.png"){
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x10,0x00,0x82 ) );
		}


	if(file=="archer_en.png"){
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x10,0x00,0x82 ) );
		}
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
          else{  
           //Get image dimensions
           mWidth = 300;
         mHeight = 50;
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

/*void LTexture::renderTile(Tile tile)
{
    //Set rendering space and render to screen
      SDL_Rect renderQuad = { tile.mBox.x, tile.mBox.y, mWidth, mHeight };

          //Set clip rendering dimensions
          if( tile.mType.clip != NULL )
                  {
                          renderQuad.w = tile.mType.clip->w;
                          renderQuad.h = tile.mType.clip->h;
                   }
                                           //Render to screen
                SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
  }

*/
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

