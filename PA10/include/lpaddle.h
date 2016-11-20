#ifndef LPADDLE_H
#define LPADDLE_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class LPaddle: public Model
{
    public:
        // Constructor
        LPaddle( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Swing();
        
        // Destructor
        ~LPaddle();

    private:
    
};

#endif
