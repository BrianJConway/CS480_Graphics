#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"
#include <string>

using namespace std;

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    
    void updateVectors();
    void processKeyboard( string direction );
    void processMouseMovement(GLfloat xoffset, GLfloat yoffset );

  private:
    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    // Angles
    GLfloat yaw;
    GLfloat pitch;
    
    // Camera options
    GLfloat moveSpeed;
    GLfloat sensitivity;
};

#endif /* CAMERA_H */
