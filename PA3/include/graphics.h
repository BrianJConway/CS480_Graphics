#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
<<<<<<< HEAD
#include "planet.h"
#include "moon.h"
=======
>>>>>>> 18809b5f73c5e259dfd3e62b9f8c55e416993cab

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height, std::string shaders[] );
    void Update(unsigned int dt, vector<string> flags);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

<<<<<<< HEAD
    Object *m_planet;
=======
    Object *m_cube;
>>>>>>> 18809b5f73c5e259dfd3e62b9f8c55e416993cab
    Object *m_moon;
};

#endif /* GRAPHICS_H */
