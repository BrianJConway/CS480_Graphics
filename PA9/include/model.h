#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
   {
    public:
        Model( string file );
        void Draw();	
		void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
		glm::mat4 getModel();
        glm::vec3 getPosition();

    protected:
        Mesh mesh;
		glm::mat4 model;
		float rotateAngle;
        btRigidBody* rigidBody;
   };
   
#endif
