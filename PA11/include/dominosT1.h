#ifndef DOMINOST1_H
#define DOMINOST1_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class DominosT1
{
    public:
        // Constructor
        DominosT1( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        
        // Destructor
        ~DominosT1s();

    private:
    
};

#endif
