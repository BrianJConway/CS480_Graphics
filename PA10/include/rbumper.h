#ifndef BUMPER_H
#define BUMPER_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class RBumper: public Model
{
    public:
        // Constructor
        RBumper( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        
        // Destructor
        ~RBumper();

    private:
    
};

#endif
