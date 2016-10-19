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
#include "planet.h"
#include "stars.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height, std::string fNames[] );
    void Update(unsigned int dt);
    void Render();
    Camera* getCamera();

  private:
    std::string ErrorString(GLenum error);
    void loadPlanets();
    void loadMoons( int planetIndex );
    bool realistic;
    bool stars;
    
    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    // Sun, all planets, and pluto
    vector<Planet*> planets;
    Stars* star;
};

#endif /* GRAPHICS_H */
