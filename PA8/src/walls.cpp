#include "walls.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Walls::Walls( btDiscreteDynamicsWorld* dynamicsWorld )
   {
    // Create collision shapes
    btCollisionShape* leftShape = new btBoxShape( btVector3( 2, 5, 25 ) );
    btCollisionShape* rightShape = new btBoxShape( btVector3( 2, 5, 25 ) );
    btCollisionShape* topShape = new btBoxShape( btVector3( 25, 5, 2 ) );
    btCollisionShape* bottomShape = new btBoxShape( btVector3( 25, 5, 2 ) );
        
    // Create motion states
    btDefaultMotionState* leftMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 25, 0, 0 ) ) );            
            
    btDefaultMotionState* rightMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( -25, 0, 0 ) ) ); 

    btDefaultMotionState* topMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 0, 20 ) ) ); 

    btDefaultMotionState* bottomMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 0, -20 ) ) ); 

    // Create rigid bodies
    btScalar mass = 0;
    btVector3 Inertia = btVector3( 0, 0, 0 );
    
    leftShape->calculateLocalInertia( mass, Inertia );
    rightShape->calculateLocalInertia( mass, Inertia );
    topShape->calculateLocalInertia( mass, Inertia );
    bottomShape->calculateLocalInertia( mass, Inertia );
    
    btRigidBody::btRigidBodyConstructionInfo leftRigidBodyCI( 
                                mass, leftMotionState, leftShape, Inertia );
    btRigidBody::btRigidBodyConstructionInfo rightRigidBodyCI( 
                                mass, rightMotionState, rightShape, Inertia );
    btRigidBody::btRigidBodyConstructionInfo topRigidBodyCI( 
                                mass, topMotionState, topShape, Inertia );
    btRigidBody::btRigidBodyConstructionInfo bottomRigidBodyCI( 
                                mass, bottomMotionState, bottomShape, Inertia );


    leftBody = new btRigidBody( leftRigidBodyCI );
    rightBody = new btRigidBody( rightRigidBodyCI );
    topBody = new btRigidBody( topRigidBodyCI );
    bottomBody = new btRigidBody( bottomRigidBodyCI );

    leftBody->setRestitution( 0.1 );
    rightBody->setRestitution( 0.1 );
    topBody->setRestitution( 0.1 );
    bottomBody->setRestitution( 0.1 );
                        
    // Add bodies to world
    dynamicsWorld->addRigidBody( leftBody );   
    dynamicsWorld->addRigidBody( rightBody );  
    dynamicsWorld->addRigidBody( topBody );    
    dynamicsWorld->addRigidBody( bottomBody );    
   }

void Walls::Update( btDiscreteDynamicsWorld* dynamicsWorld )
   {

   } 

