# PA10: Pinball

# Building and Running

## Dependencies
Uses ImageMagick to load texture images.

## Controls

W – Launch ball

A – Left Paddle

D – Right Paddle

Q – Switch to fragment lighting

Z – Switch to vertex lighting

U – Decrease ambient brightness

J – Increase ambient brightness

H – Increase specular shininess of objects

K – Decrease specular shininess of objects

Up Arrow Key – Increase spotlight size

Down Arrow Key – Decrease spotlight size

Left Arrow Key – Zoom camera out

Right Arrow Key – Zoom camera in


## CMake Instructions
Navigate to the PA10 directory. Running the executable correctly involves specifying
the type of lighting you want to load by default, choosing between "Gouraud" or
"Phong" as command-line parameters. 

```bash
mkdir build
cd build
cmake ..
make
./Tutorial Gouraud 
OR
./Tutorial Phong 
```


## Ubuntu.cse.unr.edu
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial Phong 
```
