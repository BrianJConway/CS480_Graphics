#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "model.h"
#include "sphere.h"
#include "ground.h"
#include "cylinder.h"
#include "cube.h"

class Graphics
{
  public:
    Graphics( btDiscreteDynamicsWorld* DynamicsWorld );
    ~Graphics();
    bool Initialize(int width, int height, std::string fNames[] );
    void Update(unsigned int dt);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    btDiscreteDynamicsWorld* dynamicsWorld;

    Ground *m_ground;
    Sphere *m_sphere;
    Cylinder *m_cylinder;
    Cube *m_cube;
    
   unsigned long int counter = 0;
};

#endif /* GRAPHICS_H */
