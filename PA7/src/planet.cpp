#include "planet.h"
#include <vector>
#include <cmath>

using namespace std;

Planet::Planet(int index, string fileName, double RelativeSize, double RotateSpeed, int moons, double OrbitDistance, double OrbitPeriod, bool realistic )
{
    mesh.loadMesh( fileName );
    
    planetIndex = index;
    rotateSpeed = RotateSpeed;
    numMoons = moons;
    orbitPeriod = OrbitPeriod;

    if( !realistic )
       {
        orbitDistance = index * 2.0;
        
        if( planetIndex == 9 || planetIndex > 0 && planetIndex < 5  )
            relativeSize = RelativeSize * 15.00;
        else if( planetIndex != 0 )
            relativeSize = RelativeSize * 3.75;
        else 
            relativeSize = RelativeSize;
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


    orbitAngle += planetIndex * 5;
      


    if(numMoons > 3)
    {
        numMoons = 3;
    }

    for(int i = 0; i < numMoons; i++)
    {
        Moon* moonptr = new Moon(i, "pluto.obj");
	Moons.push_back(moonptr);
    }
}

// Updates Model Location
void Planet::Update(unsigned int dt)
{
  // Initialize function/variables
  glm::mat4 translate = model;
  glm::mat4 rotate = model;
  glm::mat4 scale = model;
  
  double orbitScale = 50000.00 * orbitPeriod;
  double rotateScale = 2000.00 * rotateSpeed;
  
  if( planetIndex != 0 )
  orbitAngle += dt * M_PI/ orbitScale;
  else
  orbitAngle += dt * M_PI/ 10000;

  rotateAngle -= dt * M_PI / rotateScale;

  // Caclulate coordinates based on parametric equation for a circle
  float xPos = 0.0 + orbitDistance * glm::cos( orbitAngle );
  float zPos = 0.0 + orbitDistance * glm::sin( orbitAngle );
  

  scale = glm::scale( glm::mat4(1.0f), glm::vec3( relativeSize ) );
 
  rotate = glm::rotate( glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0,1.0, 0.0));
  
  translate = glm::translate( glm::mat4(1.0f), glm::vec3( xPos, 0.0, zPos ) );
  
  model = translate * rotate * scale; 


  // Update all moons
  for(int i = 0; i < Moons.size(); i++)
  {
	Moons[i]->UpdatePlanet(getModel());
	Moons[i]->Update(dt);
  }
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
    
    for(int i = 0; i < Moons.size(); i++)
    {
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE,  glm::value_ptr(Moons[i]->getModel()));
        Moons[i]->Draw(modelMatrix);
    }
}
