#include "domino.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Domino::Domino( string fileName, btDiscreteDynamicsWorld* dynamicsWorld, float x, float y, float z, float angle ) : Model( fileName )
   {
    // Create domino collision shape
    btCollisionShape* dominoShape = new btBoxShape( btVector3( 1, 1.5, 0.25 ) );
        
    // Create domino motion state, place 2 meters above ground
    btDefaultMotionState* dominoMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, angle, 0, 1 ), btVector3( x, y, z ) ) );            
            
    // Create Domino rigid body
    btScalar mass = 1;
    btVector3 dominoInertia = btVector3( 0, 0, 0 );
    dominoShape->calculateLocalInertia( mass, dominoInertia );
    btRigidBody::btRigidBodyConstructionInfo dominoRigidBodyCI( 
                                mass, dominoMotionState, dominoShape, dominoInertia );
    rigidBody = new btRigidBody( dominoRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 1, 1, 1 ) );
    
    rigidBody->setRestitution( 0.1 );
                        
    // Add domino to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Domino::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Domino::Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion )
   {
    btTransform trans;
    btScalar m[ 16 ];


    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
