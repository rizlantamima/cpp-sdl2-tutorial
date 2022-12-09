//
//  main.cpp
//  SDL_tutorial
//
//  Created by Rizlan Tamima on 08/12/22.
//
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* globalWindow = NULL;
    
//The surface contained by the window
SDL_Surface* globalScreenSurface = NULL;

//The image we will load and show on the screen
//SDL_Surface* globalBackgroundImage = NULL;


//Loads individual image
SDL_Surface* loadSurface( std::string path );

SDL_Surface* globalKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* globalCurrentSurface = NULL;



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

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

//Loads media
bool loadMedia()
{
    //Loading success flag
    bool load_default, load_up, load_down, load_left, load_right;
    load_default = load_up = load_down = load_left = load_right = true;
    
    
    //Load default surface
    globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("assets/background.bmp");
        
    if( globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        load_default = false;
    }

    //Load up surface
    globalKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "assets/up.bmp" );
    if( globalKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        load_up = false;
    }
    
    //Load down surface
    globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "assets/down.bmp" );
    if( globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        load_down = false;
    }
    
    //Load left surface
    globalKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "assets/left.bmp" );
    if( globalKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        load_left = false;
    }
    
    //Load right surface
    globalKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "assets/right.bmp" );
    if( globalKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        load_right = false;
    }
    

    return load_default && load_up && load_down && load_left && load_right ;
}

//Frees media and shuts down SDL
void close(){
    //Deallocate surface
    SDL_FreeSurface( globalCurrentSurface );
    globalCurrentSurface = NULL;

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
        
    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
        
    // int loopCounter = 0;
    
    //Set default current surface
    globalCurrentSurface = globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
    
    //Hack to get window to stay up && While application is running (The game loop)
    while( !quit ){
        // printf("update loop %i \n",loopCounter);
        // loopCounter++;

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            
            //User requests quit
            switch (e.type) {
                
                case SDL_QUIT:
                    quit = true;
                    break;
                
                case SDL_KEYUP:
                    printf("Keyboard type released \n");
                    printf("%u released the press \n",e.key.keysym.scancode);
                    break;
                    
                case SDL_KEYDOWN:
                    printf("Event keyboard typed triggered \n");
                    printf("%u pressed down \n",e.key.keysym.sym);
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_UP:
                            globalCurrentSurface = globalKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                        case SDLK_DOWN:
                            globalCurrentSurface = globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;
                        
                        case SDLK_LEFT:
                            globalCurrentSurface = globalKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                        case SDLK_RIGHT:
                            globalCurrentSurface = globalKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;
                        
                        default:
                            globalCurrentSurface = globalKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                    }
                    break;
                    
                default:
                    // printf("Some event happen %u \n",e.type);
                    break;
            }
            
        }
        
        
        
        //Apply the image
        SDL_BlitSurface( globalCurrentSurface, NULL, globalScreenSurface, NULL );
        
        //Update the surface
        SDL_UpdateWindowSurface( globalWindow );

        
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
    
}
