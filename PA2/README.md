# PA2: Controllable Spinning and Orbiting Cube

# Keyboard Controls

```bash
Q - Toggles direction of rotation
W - Toggles rotation on/off

LEFT MOUSE CLICK - Toggles direction of orbit
RIGHT MOUSE CLICK - Toggles orbit on/off

P - Toggles all motion on/off
```

# Building and Running

## CMake Instructions
Navigate to the PA2 directory. Running the executable correctly involves specifying
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
