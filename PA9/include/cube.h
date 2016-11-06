#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Cube: public Model
{
    public:
        // Constructor
        Cube( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );

        // Destructor
        ~Cube();

    private:
    
};

#endif
