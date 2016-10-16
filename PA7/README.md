# PA7: Solar System

# Building and Running

## Dependencies
Uses ImageMagick to load texture images.

## Controls

### NOTE
Camera controls are a little wonky, make sure when you run the program your
mouse isn't where the window will appear. After you run the program, move mouse 
into the window and then hold S until you can see the models. Then use the controls
as normal.

### Keyboard Controls
W - Camera forward
S - Camera backward
A - Camera left
D - Camera right

### Mouse Controls
Move mouse to look around

## CMake Instructions
Navigate to the PA6 directory. Running the executable correctly involves specifying
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
