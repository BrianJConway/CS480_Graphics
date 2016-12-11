#include "trapezoid.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Trapezoid::Trapezoid( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create Trapezoid collision shape
    btCollisionShape* fallShape = new btBoxShape( btVector3(1, 6.4, 1));
        
    // Create Trapezoid motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( -35, 44, 330 ) ) );            
            
    // Create Trapezoid rigid body
    btScalar mass = 10;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 1, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add Trapezoid to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

Trapezoid::~Trapezoid()
{
}

void Trapezoid::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

btVector3 Trapezoid::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}
