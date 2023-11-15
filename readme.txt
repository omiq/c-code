== MacOS ==

Check if you have SDL2:
  brew list | grep sdl2
  brew install sdl2 / brew upgrade sdl2
  brew install sdl2_image / brew upgrade sdl2_image

Get the path to the files:
  brew --cellar

Symbolic link the libraries (edit to include correct version numbers):
  ln -s /opt/homebrew/Cellar/SDL2/2.28.5/include/SDL2 ./include/SDL2  
  ln -s /opt/homebrew/Cellar/SDL2_image/2.6.3_2/include/SDL2 ./include/SDL2_image
  ln -s /opt/homebrew/Cellar/SDL2_image/2.6.3_2/lib ./lib/SDL2_image

  
