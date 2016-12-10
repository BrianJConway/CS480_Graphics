#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Room: public Model
{
    public:
        // Constructor
        Room( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        
        // Destructor
        ~Room();

    private:
    
};

#endif
