#include "cube.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Cube::Cube( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create cube collision shape
    btCollisionShape* cubeShape = new btBoxShape( btVector3( 1, 1, 1 ) );
        
    // Create cube motion state, place 50 meters above ground
    btDefaultMotionState* cubeMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 1, 1, 1 ) ) );            
            
    // Create Cube rigid body
    btScalar mass = 1;
    btVector3 cubeInertia = btVector3( 0, 0, 0 );
    cubeShape->calculateLocalInertia( mass, cubeInertia );
    btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI( 
                                mass, cubeMotionState, cubeShape, cubeInertia );
    rigidBody = new btRigidBody( cubeRigidBodyCI );
                        
    // Add cube to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Cube::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
