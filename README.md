# RocketLeague2d

## Building

Dependencies:
* [cmake](https://cmake.org/)
* [SDL2](https://libsdl.org/)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

To install dependencies on Linux:
```shell
sudo apt install cmake
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
sudo apt install libsdl2-mixer-dev
sudo apt install libsdl2-ttf-dev
```

To build the project:
```shell
cd build
cmake ..
make
```

## Usage 
```shell
server_host@128.0.0.0
$ ./rl_server <PORT>

client@192.168.x.x:
$ ./rocket_league <HOST> <PORT>
```
To run the client you must be in the build/src directory.
