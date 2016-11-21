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
#include "walls.h"
#include "rpaddle.h"
#include "lpaddle.h"
#include "back.h"
#include "rbumper.h"
#include "lbumper.h"
#include "mbumper.h"


struct Light
   {
    glm::vec4 AmbientProduct;
    glm::vec4 DiffuseProduct;
    glm::vec4 SpecularProduct;
    glm::vec4 LightPosition;
    float coneAngle;
    glm::vec3 coneDirection;
    float brightness;
   };

class Graphics
{
  public:
    Graphics( btDiscreteDynamicsWorld* DynamicsWorld );
    ~Graphics();
    bool Initialize(int width, int height, std::string fNames[] );
    void Update(unsigned int dt, string motion[] );
    void Render();
    void setLightingUniforms( Model* object );
    void swapShaders( string shader );
    void adjustLighting( string control );
    btVector3 getSphereCOM();
    int getBallNum();
    int getScore();
    Camera* getCamera();
    
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shaderGouraud;
    Shader *m_shaderPhong;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    btDiscreteDynamicsWorld* dynamicsWorld;

    Ground *m_ground;
    Sphere *m_sphere;
    Cylinder *m_cylinder;
    Cube *m_cube;
    Walls *m_walls;
    RPaddle *m_rpaddle;
    LPaddle *m_lpaddle;
    Back *m_back;
    RBumper *m_rbumper;
    LBumper *m_lbumper;
    MBumper *m_mbumper;
    
    vector<Light> lights;
    
    unsigned long int counter = 0;
    btVector3 gutter = btVector3(1.2, 3, -34);
    btVector3 lbumper = btVector3(10, 3, 20);
    btVector3 rbumper = btVector3(-10, 3, 20);
    int BallNum = 0;
    int Score = 0;
   
};

#endif /* GRAPHICS_H */
