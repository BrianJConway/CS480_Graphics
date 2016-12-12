#include "pencil.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Pencil::Pencil( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create Pencil collision shape
    btCollisionShape* fallShape = new btBoxShape( btVector3(1, 10, 1));
        
    // Create Pencil motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 0, 1), btRadians(90)), btVector3( -67.4, 30, 210 ) ) );            
            
    // Create Pencil rigid body
    btScalar mass = 1;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add Pencil to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

Pencil::~Pencil()
{
}

void Pencil::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Pencil::Start()
{
    
}

btVector3 Pencil::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}

void Pencil::setVelocity(btVector3 velocity)
{
	rigidBody->setLinearVelocity(velocity);
}
