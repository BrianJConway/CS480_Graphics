#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Trapezoid: public Model
{
    public:
        // Constructor
        Trapezoid( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        btVector3 getCOM();

        // Destructor
        ~Trapezoid();

    private:
        
};

#endif
