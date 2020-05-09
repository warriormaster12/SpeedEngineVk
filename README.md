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
Extract SDK to folder "lib" inside SpeedEngineVk
```

####  Vulkan-SDK doc provides installation guide for installing SDK succefully
![Screenshot_20200509_113228](https://user-images.githubusercontent.com/33091666/81468532-cd3d2c80-91e8-11ea-94d6-cf9ce4713e68.png)
### Build the project
```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```
### Don't forget to compile shaders 
```
$ cd EngineAssets/Shaders 
$ ./ShaderCompiler.sh
```
