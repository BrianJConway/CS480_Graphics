#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Cannon: public Model
{
    public:
        // Constructor
        Cannon( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );

        // Destructor
        ~Cannon();

    private:
        btTriangleMesh* m_objTriMesh; 
};

#endif
