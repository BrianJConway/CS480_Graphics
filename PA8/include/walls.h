#ifndef WALLS_H
#define WALLS_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Walls
{
    public:
        // Constructor
        Walls( btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld );
        
        // Destructor
        ~Walls();

    private:
        btRigidBody* topBody;
        btRigidBody* bottomBody;
        btRigidBody* leftBody;
        btRigidBody* rightBody;
    
};

#endif
