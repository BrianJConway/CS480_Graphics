#ifndef CUP_H
#define CUP_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Cup: public Model
{
    public:
        // Constructor
        Cup( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Start();
        btVector3 getCOM();

        // Destructor
        ~Cup();

    private:
};

#endif
