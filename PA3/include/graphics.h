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
#include "planet.h"
#include "moon.h"

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
    
    GLint m_planetMatrix;
    GLint m_moonMatrix;

    Object *m_planet;
    Object *m_moon;
};

#endif /* GRAPHICS_H */
