#ifndef DOMINO_H
#define DOMINO_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Domino: public Model
{
    public:
        // Constructor
        Domino( string fileName, btDiscreteDynamicsWorld* dynamicsWorld, float x, float y, float z, float angle );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion );
        
        // Destructor
        ~Domino();

    private:
    
};

#endif
