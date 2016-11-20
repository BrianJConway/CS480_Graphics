#include "rpaddle.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

RPaddle::RPaddle( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create paddle collision shape
    btCollisionShape* paddleShape = new btBoxShape( btVector3( 3.5, 2, 2 ) );
        
    // Create paddle motion state, place in socket
    btDefaultMotionState* paddleMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 1, 0), btRadians(120)), btVector3( -5, 1, -29 ) ) );            
            
    // Create Cylinder rigid body
    btScalar mass = 1;
    btVector3 paddleInertia = btVector3( 0, 0, 0 );
    paddleShape->calculateLocalInertia( mass, paddleInertia );
    btRigidBody::btRigidBodyConstructionInfo paddleRigidBodyCI( 
                                mass, paddleMotionState, paddleShape, paddleInertia );
    rigidBody = new btRigidBody( paddleRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 0, 0 ) );
    rigidBody->setAngularFactor(btVector3( 0, 1, 0 ) );
    
                        
    // Add paddle to world
    dynamicsWorld->addRigidBody( rigidBody, COL_PADDLE, paddleCollidesWith );    
   }

void RPaddle::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void RPaddle::Swing()
{
    rigidBody->setAngularVelocity(btVector3(0, 1000, 0));
    //rigidbody->applyTorqueImpulse(btVector3(0, 1000, 0));
}
