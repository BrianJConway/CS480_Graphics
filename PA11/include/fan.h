#ifndef FAN_H
#define FAN_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Fan: public Model
{
    public:
        // Constructor
        Fan( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        btVector3 getCOM();

        // Destructor
        ~Fan();

    private:
        
};

#endif
