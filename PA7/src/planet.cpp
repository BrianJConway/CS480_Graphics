#include "planet.h"
#include <vector>
#include <cmath>

Planet::Planet(int index, string fileName, float RelativeSize, float RotateSpeed, int moons, float OrbitDistance, float OrbitPeriod, bool realistic )
{
    mesh.loadMesh( fileName );
    
    planetIndex = index;
    rotateSpeed = RotateSpeed;
    numMoons = moons;
    orbitPeriod = orbitPeriod;
    
    if( !realistic )
       {
        orbitDistance = index * 2.0;
        
        if( planetIndex != 0 )
            relativeSize = RelativeSize * 4.00;
        else
            relativeSize = RelativeSize * 1.75;
       }

    else
       {
        if( planetIndex != 0 )
            orbitDistance = 1.0 + OrbitDistance;   
        else
            orbitDistance = orbitDistance;
            
        relativeSize = RelativeSize;
       }

        

    
    rotateAngle = 0.0f;
    orbitAngle = 0.0f;

    if(numMoons > 3)
    {
        numMoons = 3;
    }

    for(int i = 0; i < numMoons; i++)
    {
        // push moon into vector
    }
}

// Updates Model Location
void Planet::Update(unsigned int dt)
{
  // Initialize function/variables
  glm::mat4 translate = model;
  glm::mat4 rotate = model;
  glm::mat4 scale = model;

  rotateAngle += dt * M_PI / 5000;
  orbitAngle += dt * M_PI/ 100000;

  // Caclulate coordinates based on parametric equation for a circle
  float xPos = 0.0 + orbitDistance * glm::cos( orbitAngle );
  float zPos = 0.0 + orbitDistance * glm::sin( orbitAngle );
  

  scale = glm::scale( glm::mat4(1.0f), glm::vec3( relativeSize ) );
 
  rotate = glm::rotate( glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0,1.0, 0.0));
  
  translate = glm::translate( glm::mat4(1.0f), glm::vec3( xPos, 0.0, zPos ) );
  
  model = translate * rotate * scale; 
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
