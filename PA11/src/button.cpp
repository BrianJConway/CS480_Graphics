#include "button.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Button::Button( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create Button collision shape
    btCollisionShape* fallShape = new btBoxShape( btVector3(1, 1, 1));
        
    // Create Button motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 0, 0), 1), btVector3( -67.4, 40, 120 ) ) );            
            
    // Create Button rigid body
    btScalar mass = 1;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add Button to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

Button::~Button()
{
}

void Button::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Button::Start()
{
    
}

btVector3 Button::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}
