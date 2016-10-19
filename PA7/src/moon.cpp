#include "moon.h"
#include <vector>
#include <cmath>

Moon::Moon(int index, string fileName)
{
    mesh.loadMesh( fileName );

    Index = index;
    orbitAngle = 100 * index;
}

Moon::~Moon()
{
}

// Updates Model Location
void Moon::Update(unsigned int dt)
{
    glm::mat4 translate = model;
    glm::mat4 rotate = model;
    glm::mat4 scale = model;
      
    orbitAngle += dt * M_PI/ 100000;
    rotateAngle += dt * M_PI/1000;

    // Caclulate coordinates based on parametric equation for a circle
    float xPos = 2.0 * glm::cos( orbitAngle );
    float zPos = 2.0 * glm::sin( orbitAngle );

    scale = glm::scale( glm::mat4(1.0f), glm::vec3( 0.27268 ) );
 
    rotate = glm::rotate( glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0,1.0, 0.0));
  
    translate = glm::translate( glm::mat4(planetModel), glm::vec3( xPos, 0.0, zPos ) );

    model = translate * rotate * scale;
}

glm::mat4 Moon::getModel()
{
    return model;
}

// Draws the model by drawing each mesh
void Moon::Draw(GLint modelMatrix)
{
    // Draw meshes
    mesh.Draw();
}

void Moon::UpdatePlanet(glm::mat4 model)
{
    planetModel = model;
}
