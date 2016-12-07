#include "camera.h"
#include <string>
#include <iostream>

using namespace std;

Camera::Camera()
   {
    pos = glm::vec3( 0.0, 40.0, -60.0 );
    front = glm::vec3( 0.0, 0.0, 0.0 );
    worldUp = glm::vec3( 0.0, 1.0, 0.0 );
    
    // The right vector is the cross product of front and actual up
    right = glm::normalize( glm::cross( front, worldUp ) );
    
    // For now set up to world up, but this can change based on mous movement
    up = worldUp; 
    
    pitch = 0;
    yaw = 0;
    
    moveSpeed = 2.0f;
    sensitivity = 0.25f;
   }

Camera::~Camera()
   {

   }

bool Camera::Initialize(int w, int h)
   {
  view = glm::lookAt( glm::vec3(0.0, 40.0, -60.0), //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   500.0f); //Distance to the far plane, 
    return true;
   }

glm::mat4 Camera::GetProjection()
   {
    return projection;
   }

glm::mat4 Camera::GetView()
   {
    // Update and return view matrix
    view = glm::lookAt( glm::vec3( pos.x, pos.y, pos.z), 
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
                      
    return view;
   }

// Handle keyboard inputs
void Camera::processKeyboard( string direction )
   {
    // Move forward
    if( direction == "FORWARD" )
       {
        if( pos.z < -2.0 )
        pos += glm::vec3( 0.0, 0.0, 1.0 ) * moveSpeed;
       }
    // Move backward
    else if( direction == "BACK" )
       {
        if( pos.z > -150.0 )
        pos -= glm::vec3( 0.0, 0.0, 1.0 ) * moveSpeed;
       }
    // Move left
    else if( direction == "LEFT" )
       {
        pos -= right * moveSpeed;
       }
    // Move right
    else
       {
        pos += right * moveSpeed;
       }
   }


   
   
   


