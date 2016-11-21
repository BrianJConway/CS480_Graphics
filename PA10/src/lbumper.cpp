#include "lbumper.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

LBumper::LBumper( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create bumper collision shape
    btCollisionShape* bumperShape = new btBoxShape( btVector3( 1, 1, 1 ) );
        
    // Create bumper motion state
    btDefaultMotionState* bumperMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1), btVector3( 10, 1, 20 ) ) );            
            
    // Create bumper rigid body
    btScalar mass = 0;
    btVector3 bumperInertia = btVector3( 0, 0, 0 );
    bumperShape->calculateLocalInertia( mass, bumperInertia );
    btRigidBody::btRigidBodyConstructionInfo bumperRigidBodyCI( 
                                mass, bumperMotionState, bumperShape, bumperInertia );
    rigidBody = new btRigidBody( bumperRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 0, 0 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );
    
                        
    // Add bumper to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void LBumper::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
