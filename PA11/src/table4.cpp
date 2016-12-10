#include "table4.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Table4::Table4( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create cube collision shape
    btCollisionShape* cubeShape = new btBoxShape( btVector3( 45, 46, 65 ) );
        
    // Create cube motion state, place 2 meters above ground
    btDefaultMotionState* cubeMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( -70, -20, 150 ) ) );            
            
    // Create Table4 rigid body
    btScalar mass = 10;
    btVector3 cubeInertia = btVector3( 0, 0, 0 );
    cubeShape->calculateLocalInertia( mass, cubeInertia );
    btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI( 
                                mass, cubeMotionState, cubeShape, cubeInertia );
    rigidBody = new btRigidBody( cubeRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 0, 0, 0 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );
    
    rigidBody->setRestitution( 0.1 );
                        
    // Add cube to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Table4::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Table4::Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion )
   {
    btTransform trans;
    btScalar m[ 16 ];

    rigidBody->forceActivationState(ACTIVE_TAG);

    if( motion != "NONE" )
       {
        if( motion == "UP" )
           {
            rigidBody->setLinearVelocity( btVector3( 0, 0, 1.5 ) );
           }
        if( motion == "DOWN" )
           {
            rigidBody->setLinearVelocity( btVector3( 0, 0, -1.5 ) );
           }
        if( motion == "LEFT" )
           {
            rigidBody->setLinearVelocity( btVector3( 1.5, 0 , 0 ) );
           }
        if( motion == "RIGHT" )
           {
            rigidBody->setLinearVelocity( btVector3( -1.5, 0 , 0 ) );           
           }
       }
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
