#include "cube.h"
#include <vector>
#include <cmath>

using namespace std;

Cube::Cube( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create cube collision shape
    btCollisionShape* fallShape = new btBoxShape( btVector3( 0, 1, 0 ) );
        
    // Create cube motion state
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 10, 10 ) ) );            
            
    // Create cube rigid body
    btScalar mass = 1;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );
                        
    // Add sphere to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }
