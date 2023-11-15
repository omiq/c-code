#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int processEvents(SDL_Window *window)
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
  
  return done;
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; 
    SDL_Renderer *renderer = NULL;
 
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
      return 1;
  
    /* Create our window centered at 512x512 resolution */
    window = SDL_CreateWindow("Press Esc to Quit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              512, 512, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
    
    if(!window || !renderer) 
      return 1;
     
    int quit = 0;
    while(!quit)
    { 
      quit = processEvents(window);
      
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderClear(renderer);
      
      SDL_RenderPresent(renderer);
    }
      
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
 
    return 0;
}

