#ifndef MBUMPER_H
#define MBUMPER_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class MBumper: public Model
{
    public:
        // Constructor
        MBumper( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        
        // Destructor
        ~MBumper();

    private:
    
};

#endif
