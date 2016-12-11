#include "block.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Block::Block( string fileName, btDiscreteDynamicsWorld* dynamicsWorld, float x, float y, float z, float angle ) : Model( fileName )
   {
    // Create Block collision shape
    btCollisionShape* BlockShape = new btBoxShape( btVector3( 0.5, 0.5, 1.4 ) );
        
    // Create Block motion state, place 2 meters above ground
    btDefaultMotionState* BlockMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( btVector3(0, 1, 0), btRadians(angle)), btVector3( x, y, z ) ) );            
            
    // Create Block rigid body
    btScalar mass = 1;
    btVector3 BlockInertia = btVector3( 0, 0, 0 );
    BlockShape->calculateLocalInertia( mass, BlockInertia );
    btRigidBody::btRigidBodyConstructionInfo BlockRigidBodyCI( 
                                mass, BlockMotionState, BlockShape, BlockInertia );
    rigidBody = new btRigidBody( BlockRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 1, 1, 1 ) );
    
    rigidBody->setRestitution( 0.1 );
                        
    // Add Block to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Block::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Block::Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion )
   {
    btTransform trans;
    btScalar m[ 16 ];


    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
