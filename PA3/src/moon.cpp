#include "moon.h"
#include <iostream>

Moon::Moon( Planet* planet )
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  rotateAngle = 0.0f;
  orbitAngle = 0.0f;
  this->planet = planet;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Moon::~Moon()
{
  Vertices.clear();
  Indices.clear();
}

void Moon::Update(unsigned int dt, vector<string> motionSettings)
{
  // Create separate translation and rotation matrices based on model
  glm::mat4 trans = model;
  glm::mat4 rotate = model;
  glm::mat4 scale = model;
  
  // Save original values for position and angles
  float tempX = xPos;
  float tempZ = zPos;
  float tempOrbit = orbitAngle;
  float tempRotate = rotateAngle;

  // Set rotation angle based on toggle
  if( motionSettings[ 2 ] == "NORMAL" )
     {
      // Forward
      rotateAngle += dt * M_PI/1000;
     }
  else
     {
      // Reversed
      rotateAngle -= dt * M_PI/1000;  
     }

  // Set orbit angle based on toggle
  if( motionSettings[ 3 ] == "NORMAL" )
     {
      // Forward
      orbitAngle += dt * M_PI/3000;
     }
  else
     {
      // Reversed
      orbitAngle -= dt * M_PI/3000;  
     }
  
  // Caclulate coordinates based on parametric equation for a circle
  xPos = planet->xPos + 3.0 * glm::cos( orbitAngle );
  zPos = planet->zPos + 3.0 * glm::sin( orbitAngle );
  
  // No orbit or rotation
  if( motionSettings[ 4 ] == "PAUSE" && motionSettings[ 5 ] == "PAUSE" )
     {
      xPos = tempX;
      zPos = tempZ;
      rotateAngle = tempRotate;
      orbitAngle = tempOrbit;
      return;
     }
   
  // No rotation, just orbit
  else if( motionSettings[ 4 ] == "PAUSE" && motionSettings[ 5 ] == "START" )
     {
      rotateAngle = tempRotate;
     }
   
  // No orbit, just rotate 
  else if( motionSettings[ 4 ] == "START" && motionSettings[ 5 ] == "PAUSE" )
     {
      xPos = tempX;
      zPos = tempZ;
      orbitAngle = tempOrbit;
     }
  // Translate and rotate separately
  rotate = glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0,1.0, 0.0));
  trans = glm::translate(glm::mat4(1.0f), glm::vec3(xPos, 0.0, zPos));
  scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.27f));

  // Apply translation, rotation, and scaling to the model
  model = trans * rotate * scale;
  
}


