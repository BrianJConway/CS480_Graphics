# PA7: Solar System

# Controls

## Keyboard Controls
W - Camera forward

S - Camera backward

A - Camera left

D - Camera right

## Mouse Controls
Move mouse to look around

# Notes
Uses ImageMagick to load texture images.

Pluto is out there, if you have difficulty finding it try the "scaled" option
mentioned below.


# Building and Running

## CMake Instructions
Navigate to the PA7 directory. Running the executable correctly involves specifying
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

## EXTRA OPTIONS

### Scaled view
To see a scaled view of the solar system, type "scaled" as a command line argument
in addition to specifying shaders. You can combine this with the "stars" option.

### Star field
To add stars to the background, type "stars" as a command line argument in 
addition to specifying shaders. You can combine this with the "scaled" option.
Further planets are harder to find with this option on.


## Ubuntu.cse.unr.edu
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial -v vertex.glsl -f fragment.glsl
```
