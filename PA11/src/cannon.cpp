#include "cannon.h"
#include <vector>
#include <cmath>

using namespace std;

Cannon::Cannon( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName, m_objTriMesh  )
   {
    // Create Cannon collision shape
    btCollisionShape* CannonShape = 
                                new btBvhTriangleMeshShape( m_objTriMesh, true);
    
    // Create Cannon motion state, place 1 meter below Cannon
    btDefaultMotionState* CannonMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 81, 60, 228 ) ) );
            
    // Create groud rigid body, set mass 0 (immovable)
    btRigidBody::btRigidBodyConstructionInfo CannonRigidBodyCI( 
                      0, CannonMotionState, CannonShape, btVector3( 0, 0, 0 ) );
    rigidBody = new btRigidBody( CannonRigidBodyCI );
            
    // Add Cannon to world
    dynamicsWorld->addRigidBody( rigidBody );
   }
