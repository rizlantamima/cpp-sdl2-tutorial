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

int main(int argc, const char * argv[]) {
    
    //The window we'll be rendering to
        SDL_Window* window = NULL;
        
        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;

        //Initialize SDL
        int initializeSDL = SDL_Init( SDL_INIT_VIDEO );
        
        // Validate if the sdl initialization failed
        if( initializeSDL < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            return 0;
        }
    
        //Create a window
        window = SDL_CreateWindow("SDL Tutorial @rizlantamima", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
        // Validate if the sdl failed to create a window
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return 0;
        }
    
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );

        //Fill the surface white
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
        
        //Update the surface
        SDL_UpdateWindowSurface( window );
        
        //Hack to get window to stay up
        SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        //Destroy window
        SDL_DestroyWindow( window );

        //Quit SDL subsystems
        SDL_Quit();

        return 0;
    
}
