#include "tube.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Tube::Tube( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create Tube collision shape
    btCollisionShape* fallShape = new btBoxShape( btVector3(1, 0.7, 1));
        
    // Create Tube motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 0, 1), btRadians(30)), btVector3( 7.8, 64, 341 ) ) );            
            
    // Create Tube rigid body
    btScalar mass = 0;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 1, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add Tube to world
    dynamicsWorld->addRigidBody( rigidBody, COL_BALL, ballCollidesWith );    
   }

Tube::~Tube()
{
}

void Tube::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

btVector3 Tube::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}
