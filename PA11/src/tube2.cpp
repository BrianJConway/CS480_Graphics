#include "tube2.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Tube2::Tube2( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName, m_objTriMesh )
   {
    // Create Tube2 collision shape
    btCollisionShape* fallShape = 
                                new btBvhTriangleMeshShape( m_objTriMesh, true);
        
    // Create Tube2 motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 1, 0), btRadians(90) ), btVector3( -66, 41, 243 ) ) * btTransform( btQuaternion( btVector3(0, 0, 1), btRadians(-15)), btVector3( 0, 0, 0 ) ) );       
            
    // Create Tube2 rigid body
    btScalar mass = 0;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 1, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add Tube2 to world
    dynamicsWorld->addRigidBody( rigidBody, COL_BALL, ballCollidesWith );    
   }

Tube2::~Tube2()
{
}

void Tube2::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {

    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

btVector3 Tube2::getCOM()
{
    return rigidBody->getCenterOfMassPosition();
}
