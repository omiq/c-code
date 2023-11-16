#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "whereami.h"

// A basic game object
typedef struct GameObjects {
  int x, y;
  int width;
  int height;
  short life;
  char *name;
  SDL_Texture *image;
} GameObject;

// Store Window dimensions
int window_width;
int window_height;

// Initialize
SDL_Window *window;                    // Declare a window
SDL_Renderer *renderer;                // Declare a renderer
SDL_Surface *windowSurface;            // Window surface for blitting

// This is where we will move our characters
int processEvents(SDL_Window *window, GameObject *player)
{

  // Alternative to checking keydown event
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  // To store the event
  SDL_Event event;

  // Variable for if we should quit
  int done = 0;

  // Check for SDL events
  while(SDL_PollEvent(&event))
  {

    // Figure out which type of event it is
    switch(event.type)
    {

      // They closed the window - how rude!
      case SDL_WINDOWEVENT_CLOSE:
      {
        // Is the window open?
        if(window)
        {
          // Guess we are finished, close up!
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      } break;

      // Escape Key
      case SDL_KEYDOWN:
      {

        // Check the keyboard scancode
        switch(event.key.keysym.scancode)
        {

          // Tell the game we are done
          case SDL_SCANCODE_ESCAPE:
            done = 1;
            break;

          // Cursor scancodes
          case SDL_SCANCODE_LEFT:
            if((player->x-10)>0) player->x -= 10;
            break;

          case SDL_SCANCODE_RIGHT:
            if((player->x+player->width+10)< window_width) player->x += 10;
            break;

          case SDL_SCANCODE_UP:
            if((player->y-10)>0) player->y -= 10;
            break;

          case SDL_SCANCODE_DOWN:
            if((player->y+player->height+10)< window_height) player->y += 10;
            break;

          default:
            printf("\n%d",event.key.keysym.scancode);
            fflush(stdout);
            break;

        }
      } break;

      // End of our Main fires this event
      case SDL_QUIT:
        //quit out of the game
        done = 1;
      break;
    }
  }

  return done;
}



// Render the graphics to the screen
void doRender(SDL_Renderer *renderer, GameObject *this_game_object)
{
  // Set the drawing color to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  
  // Clear the view area
  SDL_RenderClear(renderer);

  // An exciting red box   
  //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);// Set the drawing color to red
  //SDL_Rect rect = { this_game_object->x, this_game_object->y, this_game_object->width, this_game_object->height };
  //SDL_RenderFillRect(renderer, &rect);
  

  SDL_Rect blit_dest = {this_game_object->x,this_game_object->y,32,32};
  
  int result = 1;
  // int result = SDL_BlitSurface(this_game_object->image, NULL, windowSurface, &blit_dest);
	
	SDL_RenderCopy(renderer, this_game_object->image, NULL, &blit_dest); 


  if ( result < 0 ) {
    // blit failed
    printf("%s\n", SDL_GetError());
    SDL_Quit();
  }

  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{

 char* path = NULL;
  int length, dirname_length;
  int i;

  length = wai_getExecutablePath(NULL, 0, &dirname_length);
  if (length > 0)
  {
    path = (char*)malloc(length + 1);
    if (!path)
      abort();
    wai_getExecutablePath(path, length, &dirname_length);
    path[length] = '\0';

    //printf("executable path: %s\n", path);
    //path[dirname_length] = '\0';
    //printf("  dirname: %s\n", path);
    //printf("  basename: %s\n", path + dirname_length + 1);
    //free(path);
  }

  SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

  // Initialize support for loading PNG and JPEG images
   
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            320,                               // width, in pixels
                            200,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  //SDL_GetWindowSizeInPixels(window,&window_width,&window_height);
	window_width = 320;
	window_height = 200;

  // Set up the player object and start centered
  GameObject player;
  player.width = 32;
  player.height = 32;

  windowSurface = IMG_Load("sprite.bmp");


  if (!windowSurface) {
    fprintf(stderr, "could not load image: %s/sprite.bmp \n%s\n", path, IMG_GetError());
    return 1;
  };

  player.image = SDL_CreateTextureFromSurface(renderer,windowSurface);

  if ( !player.image ) {
    printf("%s\n", SDL_GetError());
  }

  player.x = (window_width/2)-(player.width/2);
  player.y = (window_height/2)-(player.height/2);


  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  //Event loop
  while(!done)
  {
    // Check for events
    done = processEvents(window, &player);
    
    // Render display
    doRender(renderer, &player);
    
  }
  
  
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  // Clean up
  SDL_Quit();
  return EXIT_SUCCESS;
}

