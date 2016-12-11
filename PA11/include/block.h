#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Block: public Model
{
    public:
        // Constructor
        Block( string fileName, btDiscreteDynamicsWorld* dynamicsWorld, float x, float y, float z, float angle );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion );
        
        // Destructor
        ~Block();

    private:
    
};

#endif
