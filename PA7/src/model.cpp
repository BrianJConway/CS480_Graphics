#include "model.h"
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

// Constructor
Model::Model(string file)
   {
    // Load meshes
    mesh.loadMesh( file );
   }

// Draws the model by drawing each mesh
void Model::Draw()
   {
    // Draw meshes
    mesh.Draw();
   }

// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
