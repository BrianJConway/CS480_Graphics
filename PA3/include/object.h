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
    virtual void Update(unsigned int dt, vector<string> motionSettings) = 0;
    void Render();

    glm::mat4 GetModel();

  protected:
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
