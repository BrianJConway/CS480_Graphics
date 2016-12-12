#ifndef TUBE_H
#define TUBE_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Tube: public Model
{
    public:
        // Constructor
        Tube( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        btVector3 getCOM();

        // Destructor
        ~Tube();

    private:
        
};

#endif
