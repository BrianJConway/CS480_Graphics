#include "planet.h"
#include <vector>
#include <cmath>

Planet::Planet(int index, string fileName, float radius, float speed, int moons, float distanceFromSun, float orbitPeriod)
{
    mesh.loadMesh( fileName );
    Radius = distanceFromSun * 5;
    Speed = speed * 5000;
    NumMoons = moons;

    if(NumMoons > 3)
    {
        NumMoons = 3;
    }

    for(int i = 0; i < NumMoons; i++)
    {
        // push moon into vector
    }
}

// Updates Model Location
void Planet::Update(unsigned int dt)
{
  // Update angle - Change speed to change speed of orbit
  rotateAngle += dt * M_PI/Speed;

  // Updates model location - Radius determines distance from origin and angle determines speed of orbit
  model = glm::translate(glm::mat4(1.0f), glm::vec3(Radius * cos(rotateAngle), 0.0, Radius * sin(rotateAngle))) * glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 5.0, 0.0));
}

glm::mat4 Planet::getModel()
    {
     return model;
    }

// Draws the model by drawing each mesh
void Planet::Draw(GLint modelMatrix)
{
    // Draw meshes
    mesh.Draw();
    
    /*for(int i = 0; i < Moons.size(); i++)
    {
        Moons[i].mesh->Draw();
    }*/
}
