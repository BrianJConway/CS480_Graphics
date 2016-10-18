#include "camera.h"
#include <string>

using namespace std;

Camera::Camera()
   {
    pos = glm::vec3( 0.0, 0.0, 16.0 );
    front = glm::vec3( 0.0, 0.0, -1.0 );
    worldUp = glm::vec3( 0.0, 1.0, 0.0 );
    right = glm::normalize( glm::cross( front, worldUp ) );
    up = worldUp; 
    
    pitch = 0;
    yaw = 0;
    
    moveSpeed = 0.05f;
    sensitivity = 0.25f;
   }

Camera::~Camera()
   {

   }

bool Camera::Initialize(int w, int h)
   {
    view = glm::lookAt( glm::vec3(0.0, 0.0, -16.0), //Eye Position
                      glm::vec3(0.0, 0.0, -1 ), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   100.0f); //Distance to the far plane, 
    return true;
   }

glm::mat4 Camera::GetProjection()
   {
    return projection;
   }

glm::mat4 Camera::GetView()
   {
    // Update and return view matrix
    view = glm::lookAt( glm::vec3( pos.x, pos.y, pos.z), //Eye Position
                      glm::vec3( pos.x + front.x, pos.y + front.y, pos.z + front.z ), //Focus point
                      glm::vec3( up.x, up.y, up.z)); //Positive Y is up
                      
    
    return view;
   }

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::processKeyboard( string direction, GLfloat dt )
   {
    GLfloat velocity = moveSpeed;
    
    if( direction == "FORWARD" )
       {
        pos += front * velocity;
       }
    else if( direction == "BACKWARDS" )
       {
        pos -= front * velocity;
       }
    else if( direction == "LEFT" )
       {
        pos -= right * velocity;
       }
    else
       {
        pos += right * velocity;
       }
   }

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset )
   {
    // Initialize function/variables
    bool constrainPitch = true;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
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

    // Update Front, Right and Up Vectors using the updated Eular angles
     updateVectors();
    }


void Camera::updateVectors()
   {
    glm::vec3 front;
    front.x = cos( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
    front.y = sin( glm::radians( pitch ) );
    front.z = sin( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
    this->front = glm::normalize( front );
    
    right = glm::normalize( glm::cross(this->front, worldUp ) );  
    up = glm::normalize(glm::cross( right, this->front));
   }
   
   
   
   
