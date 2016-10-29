#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Sphere: public Model
{
    public:
        // Constructor
        Sphere( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );

        // Destructor
        ~Sphere();

    private:
    
};

#endif
