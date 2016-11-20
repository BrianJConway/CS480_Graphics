#include "rpaddle.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

RPaddle::RPaddle( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create paddle collision shape
    btCollisionShape* paddleShape = new btBoxShape( btVector3( 1, 1.5, 4 ) );
        
    // Create paddle motion state, place in socket
    btDefaultMotionState* paddleMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 1, 0), btRadians(120)), btVector3( -5, 1, -29 ) ) );            
            
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

void RPaddle::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btQuaternion quat = rigidBody->getOrientation();

    if(quat.getAngle() < 0.3)
    {
        rigidBody->applyTorqueImpulse(btVector3(0, 7000, 0));
    }
    if(quat.getAngle() > 2.0944)
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

void RPaddle::Swing()
{
    rigidBody->applyTorqueImpulse(btVector3(0, -7000, 0));
}
