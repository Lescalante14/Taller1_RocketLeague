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
sudo apt update
sudo apt upgrade

sudo apt install cmake
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
sudo apt install libsdl2-mixer-dev
sudo apt install libsdl2-ttf-dev
sudo apt install qtbase5-dev qt5-qmake
```

Execute the scripts to build and install the project
```shell
./build.sh
./install.sh
```

## Usage 
```shell
server_host@<HOST>
$ rl_server <PORT>

client@192.168.x.x:
$ rocket_league <HOST> <PORT>
```

## Game Commands

* Rotate up (Forward): Up arrow
* Rotate down (Backward): Down arrow
* Move right (Right): Right arrow
* Move left (Left): Left arrow
* Turbo: Left Shift
* Jump: Space bar
