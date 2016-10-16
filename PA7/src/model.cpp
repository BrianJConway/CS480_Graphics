#include "model.h"
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

// Constructor
Model::Model()
{
}

Model::Model(string fileName)
   {
    // Load meshes
    mesh.loadMesh( fileName );
   }

// Draws the model by drawing each mesh
/*void Model::Draw(GLint modelMatrix)
   {
    // Draw meshes
    mesh.Draw(modelMatrix);
   }
*/    
// Slowly moves the model
/*
void Model::Update(unsigned int dt)
   {
    // Initialize function/variables
    glm::mat4 rotate;
    
    // Set rotation angle at current time
    rotateAngle += dt * M_PI/9000;
    
    //scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f));

    // Rotate the model
    rotate = glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 1.0, 0.0));
    
    // Apply transformations to model matrix
    model = rotate;
   } 
*/
// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
