#include "model.h"
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

// Constructor
Model::Model( string file )
   {
    // Load meshes
    mesh.loadMesh( file );
   }

// Draws the model by drawing each mesh
void Model::Draw()
   {
    // Draw meshes
    mesh.Draw();
   }
    
// Updates the model based on physics
void Model::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }

// Returns vec3 of Position of Model
glm::vec3 Model::getPosition()
{
    btVector3 btCenter = rigidBody->getCenterOfMassPosition();
    return glm::vec3( btCenter.getX(), btCenter.getY(), btCenter.getZ());
    
}
