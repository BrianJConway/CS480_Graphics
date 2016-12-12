#include "ramp.h"
#include <vector>
#include <cmath>

using namespace std;

Ramp::Ramp( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName, m_objTriMesh  )
   {
    // Create Ramp collision shape
    btCollisionShape* RampShape = 
                                new btBvhTriangleMeshShape( m_objTriMesh, true);
    
    // Create Ramp motion state, place 1 meter below Ramp
    btDefaultMotionState* RampMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 81.3, 65, 95 ) ) );
            
    // Create groud rigid body, set mass 0 (immovable)
    btRigidBody::btRigidBodyConstructionInfo RampRigidBodyCI( 
                      0, RampMotionState, RampShape, btVector3( 0, 0, 0 ) );
    rigidBody = new btRigidBody( RampRigidBodyCI );
            
    // Add Ramp to world
    dynamicsWorld->addRigidBody( rigidBody );
   }
