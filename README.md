# SpeedEngineVk

## Installation guide 

### Install the project and its dependencies
```
$ git clone https://github.com/warriormaster12/SpeedEngineVk.git
$ cd SpeedEngineVk
$ git submodule init
$ git submodule update
```
```
Download Vulkan-SDK https://vulkan.lunarg.com/
```


#### additional dependencies for Windows
```
Download and install cmake-gui https://cmake.org/download/
Download and install python for compiling glslang https://www.python.org/downloads/
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
Generate compiler instruction set with cmake-gui and build https://youtu.be/LxHV-KNEG3k?t=155
```
### Shader compiling is automated 
