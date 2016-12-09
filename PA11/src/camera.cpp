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
                      glm::vec3( pos.x + front.x, pos.y + front.y, pos.z + front.z ),
                      glm::vec3( up.x, up.y, up.z)); 
                      
    return view;
   }

// Handle keyboard inputs
void Camera::processKeyboard( string direction )
   {
    // Move forward
    if( direction == "FORWARD" )
       {
        pos += front * moveSpeed;
       }
    // Move backward
    else if( direction == "BACK" )
       {
        pos -= front * moveSpeed;
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

// Handle mouse inputs
void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset )
   {
    // Initialize function/variables
    bool constrainPitch = true;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update yaw and pitch based on offsets
    yaw += xoffset;
    pitch -= yoffset;

    // Don't let user make pitch go above or below 90
    if ( constrainPitch )
       {
        if ( pitch > 89.0f )
           {
            pitch = 89.0f;
           }
        if ( pitch < -89.0f )
           {
            pitch = -89.0f;
           }
       }

    // update where our front, right, and up are based on mouse movements
     updateVectors();
    }


void Camera::updateVectors()
   {
    // New front vector
    glm::vec3 front;
    
    // Calculate components of new front vector based on new yaw and pitch
    front.x = cos( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
    front.y = sin( glm::radians( pitch ) );
    front.z = sin( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
    
    // Normalize front vector
    this->front = glm::normalize( front );
    
    // Update right and up vectors
    right = glm::normalize( glm::cross(this->front, worldUp ) );  
    up = glm::normalize(glm::cross( right, this->front));
   }
   
   
   
   


