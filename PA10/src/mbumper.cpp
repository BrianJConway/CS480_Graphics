#include "mbumper.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

MBumper::MBumper( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create bumper collision shape
    btCollisionShape* bumperShape = new btSphereShape( 4 );
        
    // Create bumper motion state
    btDefaultMotionState* bumperMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1), btVector3( 0, 1, 10 ) ) );            
            
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
    dynamicsWorld->addRigidBody( rigidBody, COL_BUMPER, bumperCollidesWith );    
   }

void MBumper::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    glm::mat4 scale;
    
    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );

    scale = glm::scale(glm::mat4(1.0f), glm::vec3(7.3f));
    
    model *= scale;
   } 
