# PA5: Assimp Model Loader

# Building and Running

## CMake Instructions
Navigate to the PA5 directory. Running the executable correctly involves specifying
the vertex shader filename with '-v [NAME].glsl' and the fragment shader
filename with '-f [NAME].glsl'. Vertex shader filename is 'vertex.glsl' and 
fragment shader filename is 'fragment.glsl'. You also have to specify the filename
of the .obj file you wish to load with '-o [NAME].obj'. Included is a file named
box.obj which can be specified with '-o box.obj'.

```bash
mkdir build
cd build
cmake ..
make
./Tutorial -v vertex.glsl -f fragment.glsl -o [OBJECT].obj
```


## Ubuntu.cse.unr.edu
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial -v vertex.glsl -f fragment.glsl -o [OBJECT].obj
```
