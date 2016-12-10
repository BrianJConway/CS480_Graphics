#ifndef TABLE4_H
#define TABLE4_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Table4: public Model
{
    public:
        // Constructor
        Table4( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion );
        
        // Destructor
        ~Table4();

    private:
    
};

#endif
