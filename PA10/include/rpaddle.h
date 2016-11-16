#ifndef RPADDLE_H
#define RPADDLE_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class RPaddle: public Model
{
    public:
        // Constructor
        RPaddle( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Swing();
        
        // Destructor
        ~RPaddle();

    private:
    
};

#endif
