# Vulkan_Opengl

# C++
C++ scripts
Commands to build:

1. Cmake from build folder 
mkdir build
cd build
cmake -G "MinGW Makefiles" .
MinGW32-make

(or)
2. Cmake from outside build folder
mkdir build
cmake -G "MinGW Makefiles" -S . -B build 
MinGW32-make

Include glew32.dll in cube folder while executing Cube_glew.cpp

lib folder is not included in this repository. 

Drive link for required lib files ( https://drive.google.com/drive/u/1/folders/1e2XTAf4MCXus7fuNGw7480hNPivhjhop )