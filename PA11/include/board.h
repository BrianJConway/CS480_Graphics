#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Board: public Model
{
    public:
        // Constructor
        Board( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        btVector3 getCOM();

        // Destructor
        ~Board();

    private:
       
};

#endif
