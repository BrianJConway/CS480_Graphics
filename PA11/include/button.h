#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Button: public Model
{
    public:
        // Constructor
        Button( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Start();
        btVector3 getCOM();

        // Destructor
        ~Button();

    private:
};

#endif
