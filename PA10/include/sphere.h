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
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Start();
        btVector3 getCOM();

        // Destructor
        ~Sphere();

    private:
        btVector3 start = btVector3(-24.1019, 3, -25.0097);
};

#endif
