#include "planet.h"
#include <cmath>

Planet::Planet(float radius, float speed, int moons, bool saturn, string fileName)
{
    mesh.loadMesh( fileName );
    Radius = radius;
    Speed = speed;
    NumMoons = moons;
    IsSaturn = saturn;

    if(NumMoons > 3)
    {
        NumMoons = 3;
    }

    /*for(int i = 0; i < NumMoons; i++)
    {
        Moons.push_back(Moon(data);
    }*/
}

Planet::~Planet()
{
}

// Updates Model Location
void Planet::Update(unsigned int dt)
{
  // Update angle - Change speed to change speed of orbit
  rotateAngle += dt * M_PI/Speed;

  // Updates model location - Radius determines distance from origin and angle determines speed of orbit
  model = glm::translate(glm::mat4(1.0f), glm::vec3(Radius * cos(rotateAngle), 0.0, Radius * sin(rotateAngle))) * glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 5.0, 0.0));
}

// Returns mat4 of model
/*glm::mat4 Planet::GetModel()
{
  return model;
}*/

// Draws the models by drawing each mesh
void Planet::Draw(GLint modelMatrix)
{
    // Draw planet
    mesh.Draw();
    
    // Draw moons
    /*for(int i = 0; i < Moons.size(); i++)
    {
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Moons[i]->getModel()));
        Moons[i].mesh->Draw();
    }*/
}
