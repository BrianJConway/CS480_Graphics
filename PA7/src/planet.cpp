#include "planet.h"
#include <vector>
#include <cmath>

using namespace std;

Planet::Planet(int index, string fileName, double RelativeSize, double RotateSpeed, int moons, double OrbitDistance, double OrbitPeriod, bool realistic )
   {
    // Initialize data members
    planetIndex = index;
    rotateSpeed = RotateSpeed;
    numMoons = moons;
    orbitPeriod = OrbitPeriod;
    rotateAngle = 0.0f;
    orbitAngle = 0.0f;
    orbitAngle += planetIndex * 5;

    // Load model
    mesh.loadMesh( fileName );

    // Check if realism toggled off
    if( !realistic )
       {
        // Scale orbit distance with a constant value
        orbitDistance = index * 2.0;
        
        // Check if pluto or any of the inner planets
        if( planetIndex == 9 || planetIndex > 0 && planetIndex < 5  )
           {
            // Scale inner planets and pluto up
            relativeSize = RelativeSize * 15.00;
           }
        // Otherwise, check for not the sun
        else if( planetIndex != 0 )
           {
            // Scale outer planets up a little
            relativeSize = RelativeSize * 3.75;
           }
        // Otherwise, assume the sun
        else
           { 
            // Keep sun the same size
            relativeSize = RelativeSize;
           }
       }
    // Otherwise, assume realism is on
    else
       {
        // Check if not the sun
        if( planetIndex != 0 )
           {
            // Set realistic orbit distances
            orbitDistance = 1.0 + OrbitDistance;
           }   
        else
           {
            orbitDistance = orbitDistance;
           }
            
        // Set realistic relative size
        relativeSize = RelativeSize;
       }


    // Limit number of moons rendered 
    if(numMoons > 6)
    {
        numMoons = 6;
    }

    // Generate moons
    for(int i = 0; i < numMoons; i++)
    {
        Moon* moonptr = new Moon( i, planetIndex, realistic );
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
  
  // Scale orbits accordingly
  if( planetIndex != 0 )
  orbitAngle += dt * M_PI/ orbitScale;
  else
  orbitAngle += dt * M_PI/ 10000;

  rotateAngle -= dt * M_PI / rotateScale;

  // Caclulate coordinates based on parametric equation for a circle
  float xPos = 0.0 + orbitDistance * glm::cos( orbitAngle );
  float zPos = 0.0 + orbitDistance * glm::sin( orbitAngle );
  

  // Scale, rotate, and make planet orbit
  scale = glm::scale( glm::mat4(1.0f), glm::vec3( relativeSize ) );
  rotate = glm::rotate( glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0,1.0, 0.0));
  translate = glm::translate( glm::mat4(1.0f), glm::vec3( xPos, 0.0, zPos ) );
  
  // Apply transformations 
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

    // Draw the moons    
    for(int i = 0; i < Moons.size(); i++)
       {
	    glUniformMatrix4fv(modelMatrix, 1, GL_FALSE,  glm::value_ptr(Moons[i]->getModel()));
        Moons[i]->Draw(modelMatrix);
       }
}
