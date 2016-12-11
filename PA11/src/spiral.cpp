#include "spiral.h"
#include <vector>
#include <cmath>

using namespace std;

Spiral::Spiral( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName, m_objTriMesh  )
   {
    // Create Spiral collision shape
    btCollisionShape* SpiralShape = 
                                new btBvhTriangleMeshShape( m_objTriMesh, true);
    
    // Create Spiral motion state, place 1 meter below Spiral
    btDefaultMotionState* SpiralMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 72, 120, 345 ) ) );
            
    // Create groud rigid body, set mass 0 (immovable)
    btRigidBody::btRigidBodyConstructionInfo SpiralRigidBodyCI( 
                      0, SpiralMotionState, SpiralShape, btVector3( 0, 0, 0 ) );
    rigidBody = new btRigidBody( SpiralRigidBodyCI );
            
    // Add Spiral to world
    dynamicsWorld->addRigidBody( rigidBody );
   }
