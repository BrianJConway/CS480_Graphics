#ifndef RAMP_H
#define RAMP_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Ramp: public Model
{
    public:
        // Constructor
        Ramp( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );

        // Destructor
        ~Ramp();

    private:
        btTriangleMesh* m_objTriMesh; 
};

#endif
