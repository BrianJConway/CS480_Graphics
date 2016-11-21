#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0, //<Collide with nothing
    COL_PADDLE = BIT(0), //<Collide with paddle
    COL_WALL = BIT(1), //<Collide with walls
    COL_BALL = BIT(2), //<Collide with ball
    COL_BUMPER = BIT(3) //Collide with bumper
};

class Model 
   {
    public:
        Model( string file );
        Model( string file, btTriangleMesh *& objTriMesh );
        void Draw();	
		void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
		glm::mat4 getModel();
		float getShininess();
		void adjustShininess( string control );

    protected:
        Mesh mesh;
		glm::mat4 model;
		float rotateAngle;
		float shininess;
        btRigidBody* rigidBody;

        int paddleCollidesWith = COL_BALL;
        int wallCollidesWith = COL_BALL;
        int ballCollidesWith = COL_PADDLE | COL_WALL | COL_BUMPER;
        int bumperCollidesWith = COL_BALL;
   };
   
#endif
