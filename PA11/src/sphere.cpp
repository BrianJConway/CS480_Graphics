#include "sphere.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Sphere::Sphere( string fileName, btDiscreteDynamicsWorld* dynamicsWorld, float x, float y, float z ) : Model( fileName )
   {
    // Create sphere collision shape
    btCollisionShape* fallShape = new btSphereShape( 2 );
        
    // Create sphere motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( x, y, z ) ) );            
            
    // Create Sphere rigid body
    btScalar mass = 10;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 1, 1, 1 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add sphere to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

Sphere::~Sphere()
{
}

void Sphere::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    if( cannon.distance(rigidBody->getCenterOfMassPosition()) < 2 )
       {
        count++;

        if( count >= 1000 )
        rigidBody->applyCentralImpulse( btVector3( 0, 100, 80 ) );
        launched = true;
       }
    
    if( spiralPoint.distance(rigidBody->getCenterOfMassPosition()) < 4 )
       {
        passed = true;
       }
        
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Sphere::Start()
{
    started = true;
    
    if(start.distance(rigidBody->getCenterOfMassPosition()) < 2)
    {
        rigidBody->applyCentralImpulse( btVector3(0,0,10));
    }
}


btVector3 Sphere::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}
