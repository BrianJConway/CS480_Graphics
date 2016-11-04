# PA8: Bullet Demo

# Building and Running

## Dependencies
Uses ImageMagick to load texture images.

## Controls

w - move cube forward

s - move cube backward

a - move cube left

d - move cube right

## CMake Instructions
Navigate to the PA8 directory. Running the executable correctly involves specifying
the vertex shader filename with '-v [NAME].glsl' and the fragment shader
filename with '-f [NAME].glsl'. Vertex shader filename is 'vertex.glsl' and 
fragment shader filename is 'fragment.glsl'. 

```bash
mkdir build
cd build
cmake ..
make
./Tutorial -v vertex.glsl -f fragment.glsl 
```


## Ubuntu.cse.unr.edu
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial -v vertex.glsl -f fragment.glsl 
```
