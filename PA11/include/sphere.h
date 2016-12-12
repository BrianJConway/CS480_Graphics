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
        Sphere( string fileName, btDiscreteDynamicsWorld* dynamicsWorld, float x, float y, float z );        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Start();
        btVector3 getCOM();
        static bool launched;
        static bool passed;
        static int launchCount;
        bool started = false;
        // Destructor
        ~Sphere();

    private:
        int count = 0;
        btVector3 cannon = btVector3(80.5, 52.7, 223);
        btVector3 start = btVector3( 81.3, 77, 86 ); 
        btVector3 spiralPoint = btVector3( 66.749, 79.0155, 353.526 );
};

#endif
