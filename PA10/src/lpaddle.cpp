#include "lpaddle.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

LPaddle::LPaddle( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create paddle collision shape
    btCollisionShape* paddleShape = new btBoxShape( btVector3( 1, 3, 6 ) );
        
    // Create paddle motion state, place in socket
    btDefaultMotionState* paddleMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 1, 0), btRadians(80)), btVector3( 10, 1, -28 ) ) );            
            
    // Create Cylinder rigid body
    btScalar mass = 100;
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

void LPaddle::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btQuaternion quat = rigidBody->getOrientation();

    if(quat.getAngle() > 3)
    {
        rigidBody->applyTorqueImpulse(btVector3(0, -7000, 0));
    }
    if(quat.getAngle() < 1.28)
    {
        rigidBody->setAngularVelocity(btVector3(0,0,0));
    }

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void LPaddle::Swing()
{
    rigidBody->applyTorqueImpulse(btVector3(0, 7000, 0));
}
