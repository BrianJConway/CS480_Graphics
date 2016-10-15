# PA6: Assimp Model Loader with textures

# Building and Running

## Dependencies
Uses ImageMagick to load texture images.

## IMPORTANT 
So for some reason some of us need "FindAssimp.cmake" or "Findassimp.cmake" 
in order for the cmake to find ASSIMP, so both are in the repo but having both
might also not make it compile. So you might have to check which one makes it 
so our program compiles on your machine.

## CMake Instructions
Navigate to the PA6 directory. Running the executable correctly involves specifying
the vertex shader filename with '-v [NAME].glsl' and the fragment shader
filename with '-f [NAME].glsl'. Vertex shader filename is 'vertex.glsl' and 
fragment shader filename is 'fragment.glsl'. You also have to specify the filename
of the model you wish to load with '-o [NAME]'. Included is a file named
buddha.obj which can be specified with '-o buddha.obj'.

```bash
mkdir build
cd build
cmake ..
make
./Tutorial -v vertex.glsl -f fragment.glsl -o [OBJECT]
```


## Ubuntu.cse.unr.edu
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial -v vertex.glsl -f fragment.glsl -o [OBJECT]
```
