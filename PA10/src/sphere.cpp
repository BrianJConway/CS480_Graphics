#include "sphere.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Sphere::Sphere( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create sphere collision shape
    btCollisionShape* fallShape = new btSphereShape( 1 );
        
    // Create sphere motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( -23, 3, -20 ) ) );            
            
    // Create Sphere rigid body
    btScalar mass = 10;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 0, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 1, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add sphere to world
    dynamicsWorld->addRigidBody( rigidBody, COL_BALL, ballCollidesWith );    
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
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Sphere::Start()
{
    if(start.distance(rigidBody->getCenterOfMassPosition()) < 1)
    {
        rigidBody->applyCentralImpulse( btVector3(0,0,1000));
    }
}

void Sphere::Left()
{
    if(left.distance(rigidBody->getCenterOfMassPosition()) < 3)
    {
        rigidBody->applyCentralImpulse( btVector3(-200,0,1000));
    }
}

void Sphere::Right()
{
    if(right.distance(rigidBody->getCenterOfMassPosition()) < 3)
    {
        rigidBody->applyCentralImpulse( btVector3(200,0,1000));
    }
}

btVector3 Sphere::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}
