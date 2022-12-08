//
//  main.cpp
//  SDL_tutorial
//
//  Created by Rizlan Tamima on 08/12/22.
//
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* globalWindow = NULL;
    
//The surface contained by the window
SDL_Surface* globalScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* globalHelloWorld = NULL;




//Starts up SDL and creates window
bool init(){
    
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    int initializeSDL = SDL_Init( SDL_INIT_VIDEO );
    // Validate if the sdl initialization failed
    if( initializeSDL < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    //Create window
    globalWindow = SDL_CreateWindow( "A Game From Scratch with C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    // Validate if the SDL failed to create a window
    if( globalWindow == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    //Get window surface
    globalScreenSurface = SDL_GetWindowSurface( globalWindow );

    
    
    return success;
}

//Loads media
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    globalHelloWorld = SDL_LoadBMP( "assets/background.bmp" );
    if( globalHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "sdl-tutorial/assets/background.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

//Frees media and shuts down SDL
void close(){
    //Deallocate surface
    SDL_FreeSurface( globalHelloWorld );
    globalHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( globalWindow );
    globalWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}



int main(int argc, const char * argv[]) {
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
        return 0;
    }
    
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return 0;
    }
    
    //Apply the image
    SDL_BlitSurface( globalHelloWorld, NULL, globalScreenSurface, NULL );
    
    //Update the surface
    SDL_UpdateWindowSurface( globalWindow );
    
    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while( quit == false ){
        
        while( SDL_PollEvent( &e ) ){
            if( e.type == SDL_QUIT ){
                quit = true;
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
    
}
