#include "stars.h"
#include <vector>
#include <cmath>

Stars::Stars()
{
    string fileName = "stars.obj";
    mesh.loadMesh( fileName );
}

// Updates Model Location
void Stars::Update(unsigned int dt)
{
  model = glm::scale( glm::mat4(1.0f), glm::vec3( 200 ) );
}

glm::mat4 Stars::getModel()
    {
     return model;
    }

// Draws the model by drawing each mesh
void Stars::Draw(GLint modelMatrix)
{
    // Draw meshes
    mesh.Draw();   
}
