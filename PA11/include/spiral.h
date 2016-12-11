#ifndef SPIRAL_H
#define SPIRAL_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Spiral: public Model
{
    public:
        // Constructor
        Spiral( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );

        // Destructor
        ~Spiral();

    private:
        btTriangleMesh* m_objTriMesh; 
};

#endif
