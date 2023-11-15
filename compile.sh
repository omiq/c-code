#!/bin/sh
#gcc "$1" -o "$2" -F/Library/Frameworks -framework SDL2 -I/Library/Frameworks/SDL2.framework/Headers -rpath @executable_path/
gcc "$1" -o "$2" -F/Library/Frameworks -framework SDL2 -Iinclude/SDL2 -rpath @executable_path/

