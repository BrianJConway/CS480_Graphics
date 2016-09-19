#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
using namespace std;

#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
<<<<<<< HEAD
    virtual void Update(unsigned int dt, vector<string> motionSettings) = 0;
=======
    void Update(unsigned int dt, vector<string> motionSettings);
>>>>>>> 18809b5f73c5e259dfd3e62b9f8c55e416993cab
    void Render();

    glm::mat4 GetModel();

<<<<<<< HEAD
  protected:
=======
  private:
>>>>>>> 18809b5f73c5e259dfd3e62b9f8c55e416993cab
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float orbitAngle;
    float rotateAngle;
    float xPos;
    float zPos;
};

#endif /* OBJECT_H */
