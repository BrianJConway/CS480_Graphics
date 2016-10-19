#include "moon.h"
#include <vector>
#include <cmath>

Moon::Moon(int index, string fileName)
{
    mesh.loadMesh( fileName );
}

Moon::~Moon()
{
}

// Updates Model Location
void Moon::Update(unsigned int dt)
{
    // Update angle - Change speed to change speed of orbit
    rotateAngle += dt * M_PI/1000;

    // Updates model location - Radius determines distance from origin and angle determines speed of orbit
    model = glm::translate(glm::mat4(planetModel), glm::vec3(5 * cos(rotateAngle), 0.0, 5 * sin(rotateAngle))) 
							* glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 5.0, 0.0));
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
