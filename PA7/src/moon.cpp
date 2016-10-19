#include "moon.h"
#include <vector>
#include <cmath>

Moon::Moon( int MoonIndex, int PlanetIndex, bool realistic )
   {
    // Initialize function/variables
    string fileName = "moon.obj";
    
    // Load the model for the moon
    mesh.loadMesh( fileName );
    
    // Set data members
    planetIndex = PlanetIndex;
    moonIndex = MoonIndex;
    orbitAngle = 500 * moonIndex;
   }

Moon::~Moon()
   {

   }

// Updates Model, accurate for earth and approximated for everyone else
void Moon::Update(unsigned int dt)
   {
    // Initialize function/variables
    glm::mat4 translate = model;
    glm::mat4 rotate = model;
    glm::mat4 scale = model;
    float xPos, zPos, orbitDistance;
    rotateAngle += dt * M_PI/1000;
    
    // Offset orbit speeds  
    orbitAngle += dt * M_PI/ 100000 * moonIndex;

    
    // Offset orbit distancees, a bit extra for neptune
    if( planetIndex == 8 )
    orbitDistance = 2.1 + ( .2 * moonIndex );
    else
    orbitDistance = 1.5 + ( .2 * moonIndex );
   

    // Check if earth
    if( planetIndex == 3 )
       {
        // Scale for earth's moon
        scale = glm::scale( glm::mat4(1.0f), glm::vec3( 0.27268 ) );
        
        // Caclulate orbit coordinates based on parametric equation for a circle
        xPos = 2.0 * glm::cos( orbitAngle );
        zPos = 2.0 * glm::sin( orbitAngle );
       }
    // Otherwise, assume not earth   
    else
       {
        // Scale for every other moon
        scale = glm::scale( glm::mat4(1.0f), glm::vec3( 0.1000 ) );
        
        // Caclulate orbit coordinates based on parametric equation for a circle
        xPos = orbitDistance * glm::cos( orbitAngle );
        zPos = orbitDistance * glm::sin( orbitAngle );
       }

    // Rotate moon
    rotate = glm::rotate( glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0,1.0, 0.0));
  
    // Orbit the planet
    translate = glm::translate( glm::mat4(planetModel), glm::vec3( xPos, 0.0, zPos ) );

    // Apply transformations
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
