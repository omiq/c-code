#include "SDL.h"
#include <stdio.h>

typedef struct GameObjects {
  int x, y;
  int width;
  int height;
  short life;
  char *name;
} GameObject;

int processEvents(SDL_Window *window, GameObject *player)
{
  SDL_Event event;
  int done = 0;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
        }
      }
      break;
      case SDL_QUIT:
        //quit out of the game
        done = 1;
      break;
    }
  }
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT])
  {
    player->x -= 10;
  }
  if(state[SDL_SCANCODE_RIGHT])
  {
    player->x += 10;
  }
  if(state[SDL_SCANCODE_UP])
  {
    player->y -= 10;
  }
  if(state[SDL_SCANCODE_DOWN])
  {
    player->y += 10;
  }
  
  return done;
}

// Render the graphics to the screen
void doRender(SDL_Renderer *renderer, GameObject *this_game_object)
{
  //set the drawing color to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  
  //Clear the screen
  SDL_RenderClear(renderer);
  
  //set the drawing color to red
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_Rect rect = { this_game_object->x, this_game_object->y, this_game_object->width, this_game_object->height };
  SDL_RenderFillRect(renderer, &rect);
  
  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
  SDL_Window *window;                    // Declare a window
  SDL_Renderer *renderer;                // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
   
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            320,                               // width, in pixels
                            200,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  int window_width;
  int window_height;
  SDL_GetWindowSizeInPixels(window,&window_width,&window_height);

  GameObject player;
  player.x = window_width/2;
  player.y = window_height/2;
  player.width = 32;
  player.height = 32;

  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &player);
    
    //Render display
    doRender(renderer, &player);
    
    //don't burn up the CPU
    SDL_Delay(10);
  }
  
  
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  // Clean up
  SDL_Quit();
  return EXIT_SUCCESS;
}

