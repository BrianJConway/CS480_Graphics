#ifndef PENCIL_H
#define PENCIL_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Pencil: public Model
{
    public:
        // Constructor
        Pencil( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Start();
        btVector3 getCOM();

        // Destructor
        ~Pencil();

    private:
};

#endif
