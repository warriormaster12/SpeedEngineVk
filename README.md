# SpeedEngineVk

## Installation guide 

### Install the project and its dependencies
```
$ git clone https://github.com/warriormaster12/SpeedEngineVk.git
$ cd SpeedEngineVk
$ git submodule init
$ git submodule update
```
#### additional dependencie for Windows
```
Download cmake-gui and install https://cmake.org/download/
```
```
Download Vulkan-SDK https://vulkan.lunarg.com/
```

####  Vulkan-SDK doc provides installation guide for installing SDK succefully
![Screenshot_20200509_113228](https://user-images.githubusercontent.com/33091666/81468532-cd3d2c80-91e8-11ea-94d6-cf9ce4713e68.png)
### Build the project
#### Linux
```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```
#### Windows 
```
create "build" folder
Generate build with cmake-gui and build https://youtu.be/LxHV-KNEG3k?t=155
```
### Don't forget to compile shaders 
#### Linux
```
$ cd EngineAssets/Shaders 
$ ./ShaderCompiler.sh
```
#### Windows
```
go to "EngineAssets/Shaders" directory
execute ShaderCompiler.bat
```
