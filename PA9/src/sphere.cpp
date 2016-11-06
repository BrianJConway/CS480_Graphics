#include "sphere.h"
#include <vector>
#include <cmath>

using namespace std;

Sphere::Sphere( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create sphere collision shape
    btCollisionShape* fallShape = new btSphereShape( 1 );
        
    // Create sphere motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 10, -10 ) ) );            
            
    // Create Sphere rigid body
    btScalar mass = 1;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );
                        
    // Add sphere to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }
