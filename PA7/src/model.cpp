#include "model.h"
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

// Constructor
Model::Model()
{
}

Model::Model(string file)
   {
    // Load meshes
    mesh.loadMesh( file );
   }

// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
