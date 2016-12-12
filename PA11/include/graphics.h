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
#include "room.h"
#include "table1.h"
#include "table2.h"
#include "table3.h"
#include "table4.h"
#include "sphere.h"
#include "ground.h"
#include "ramp.h"
#include "domino.h"
#include "cannon.h"
#include "top.h"

// #include "rampThing.h"
#include "spiral.h"

#include "sugar.h"
#include "cup.h"
#include "pencil.h"
#include "trapezoid.h"
#include "board.h"
#include "block.h"
#include "fan.h"
#include "tube.h"
#include "tube2.h"
#include "button.h"

const int NUM_DOMINOS = 100;

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
    
    Room* m_room;
    Ground* m_ground;
    Ground* m_ceiling;
    Table1* m_table1;
    Table2* m_table2;
    Table3* m_table3;
    Table4* m_table4;    
    
    Sphere* m_sphere;
    vector<Sphere*> spheres;
    
    // Table 1 objects
    Ramp* m_ramp;
    vector<Domino*> dominos;
    Domino* m_domino1;
    Cannon* m_cannon;
    
    // Table 2 objects
//    RampThing* m_rampThing1;
//    RampThing* m_rampThing2;
    Spiral* m_spiral;
    
    // Table 3 objects
    vector<Domino*> dominos3;
    Domino* m_domino3;
    Board* m_board;
    Trapezoid* m_trapezoid;

    // Table 4 objects
    Sugar* m_sugar;
    Cup* m_cup;
    Top* m_top;
    Pencil* m_pencil;
    vector<Block*> blocks;
    Block* m_block;
	Fan* m_fan;
	Tube* m_tube;
	Tube2* m_tube2;
	Button* m_button;

    vector<Light> lights;
    
    unsigned long int counter = 0;
    btVector3 gutter = btVector3(1.2, 3, -34);
    btVector3 lbumper = btVector3(10, 3, 20);
    btVector3 rbumper = btVector3(-10, 3, 20);
    int BallNum = 0;
    int Score = 0;
   
};

#endif /* GRAPHICS_H */
