#include "ground.h"
#include <vector>
#include <cmath>

using namespace std;

Ground::Ground( int yPos, btDiscreteDynamicsWorld* dynamicsWorld )
   {
    // Create cube collision shape
    btCollisionShape* cubeShape = new btBoxShape( btVector3( 2000, 1, 2000 ) );
        
    // Create cube motion state, place 2 meters above ground
    btDefaultMotionState* cubeMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, yPos, 0 ) ) );            
            
    // Create Table1 rigid body
    btScalar mass = 0;
    btVector3 cubeInertia = btVector3( 0, 0, 0 );
    cubeShape->calculateLocalInertia( mass, cubeInertia );
    btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI( 
                                mass, cubeMotionState, cubeShape, cubeInertia );
    btRigidBody* rigidBody = new btRigidBody( cubeRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 0, 0 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );
    
    rigidBody->setRestitution( 0.1 );
                        
    // Add cube to world
    dynamicsWorld->addRigidBody( rigidBody );
   }
