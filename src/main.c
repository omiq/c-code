#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include <SDL_image.h>
#include "whereami.h"


// A basic game object
typedef struct GameObjects {
  int x, y;
  int width;
  int height;
  int speed;
} GameObject;

GameObject brick;
GameObject player;


// Store Window dimensions
int window_width;
int window_height;

// Initialize
SDL_Window *window;                    // Declare a window
SDL_Renderer *renderer;                // Declare a renderer
SDL_Surface *player_surface;           // Window surface for blitting
SDL_Surface *brick_surface;            // Window surface for blitting
SDL_Texture *player_texture;           // Player sprite graphic
SDL_Texture *brick_texture;            // Brick graphic


// This is where user actions happen
int processEvents(SDL_Window *window)
{

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

void draw_image(SDL_Texture *image, int x, int y)
{
  SDL_Rect blit_dest = {x,y,32,32};
  
  int result = SDL_RenderCopy(renderer, image, NULL, &blit_dest); 

  if ( result < 0 ) {
    // blit failed
    printf("Error drawing %s\n", SDL_GetError());
    SDL_Quit();
  }
}

void check_controls()
{

  // Alternative to checking keydown event
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  // Cursor scancodes
  if(state[SDL_SCANCODE_LEFT]) {
    if((player.x-player.speed)>0) player.x -= player.speed;
  };

  if(state[SDL_SCANCODE_RIGHT]) {
    if((player.x+player.width+player.speed)< window_width) player.x += player.speed;
  };

  if(state[SDL_SCANCODE_UP]) {
    if((player.y-player.speed)>0) player.y -= player.speed;
  };

  if(state[SDL_SCANCODE_DOWN]) {
    if((player.y+player.height+player.speed)< window_height) player.y += player.speed;
  };
  

}

// Render the graphics to the screen
void doRender(SDL_Renderer *renderer)
{
  // Set the drawing color to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  
  // Clear the view area
  SDL_RenderClear(renderer);

  // An exciting red box   
  //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);// Set the drawing color to red
  //SDL_Rect rect = { this_game_object->x, this_game_object->y, this_game_object->width, this_game_object->height };
  //SDL_RenderFillRect(renderer, &rect);

  for(int row = brick.y; row < (window_height); row += 32) {
    for(int col = brick.x; col < (window_width); col += 32) {
      draw_image(brick_texture, col, row); 
    }  
  }

  if(brick.x > -32) brick.x--; else brick.x = 0;

  draw_image(player_texture, player.x, player.y); 

  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{

  // Initialize SDL2
  SDL_Init(SDL_INIT_EVERYTHING);              
   
  //Create an application window with the following settings:
  window = SDL_CreateWindow("SDL2 Demo",                       // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            320,                               // width, in pixels
                            200,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  SDL_GetWindowSizeInPixels(window,&window_width,&window_height);
	
  // If GetwindowSize doesn't work you can hard code
  // window_width = 320;
	// window_height = 200;


  GameObject brick;
  brick.width = 32;
  brick.height = 32;
  brick.x = 10;
  brick.y = 10;
  brick_surface = IMG_Load("./brick.png");
  if (!brick_surface) {
    fprintf(stderr, "could not load brick image: %s\n", IMG_GetError());
    exit(1);
  }
  else
  {
    brick_texture = SDL_CreateTextureFromSurface(renderer,brick_surface);
  };


  // Set up the player object and start centered
  player.width = 32;
  player.height = 32;
  player.x = (window_width/2)-(player.width/2);
  player.y = (window_height/2)-(player.height/2);
  player.speed = 1;
  player_surface = IMG_Load("./sprite.png");
  if (!player_surface) {
    fprintf(stderr, "could not load player image: %s\n", IMG_GetError());
    exit(1);
  }
  else
  {
    player_texture = SDL_CreateTextureFromSurface(renderer,player_surface);
  };

  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  //Event loop
  while(!done)
  {


    // Check keyboard and joystick
    check_controls();

    // Check for events
    done = processEvents(window);
    
    // Render display
    doRender(renderer);
    
  }
  
  
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  // Clean up
  SDL_Quit();
  return EXIT_SUCCESS;
}

