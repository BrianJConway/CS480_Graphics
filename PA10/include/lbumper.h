#ifndef LBUMPER_H
#define LBUMPER_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class LBumper: public Model
{
    public:
        // Constructor
        LBumper( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        
        // Destructor
        ~LBumper();

    private:
    
};

#endif
