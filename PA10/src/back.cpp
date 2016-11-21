#include "back.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Back::Back( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create back collision shape
    btCollisionShape* backShape = new btBoxShape( btVector3( 1, 1, 1 ) );
        
    // Create back motion state
    btDefaultMotionState* backMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion(0, 0, 0, 1), btVector3( 0, 1, 5 ) ) );            
            
    // Create back rigid body
    btScalar mass = 0;
    btVector3 backInertia = btVector3( 0, 0, 0 );
    backShape->calculateLocalInertia( mass, backInertia );
    btRigidBody::btRigidBodyConstructionInfo backRigidBodyCI( 
                                mass, backMotionState, backShape, backInertia );
    rigidBody = new btRigidBody( backRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 0, 0 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );
    
                        
    // Add back to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Back::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
