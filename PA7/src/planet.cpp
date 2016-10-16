#include "planet.h"
#include <vector>
#include <cmath>

Planet::Planet(float radius, float speed, int moons, bool saturn)
{
    Radius = radius;
    Speed = speed;
    NumMoons = moons;
    IsSaturn = saturn;

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
  angle += dt * M_PI/Speed;

  // Updates model location - Radius determines distance from origin and angle determines speed of orbit
  model = glm::translate(glm::mat4(1.0f), glm::vec3(Radius * cos(angle), 0.0, Radius * sin(angle))) * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
}

// Returns mat4 of model
glm::mat4 Planet::GetModel()
{
  return model;
}

// Draws the model by drawing each mesh
void Model::Draw()
{
    // Draw meshes
    mesh.Draw();
    
    for(int i = 0; i < Moons.size(); i++)
    {
        Moons[i].mesh->Draw();
    }
}
