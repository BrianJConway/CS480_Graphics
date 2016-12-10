#ifndef TABLE1_H
#define TABLE1_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Table1: public Model
{
    public:
        // Constructor
        Table1( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, string motion );
        
        // Destructor
        ~Table1();

    private:
    
};

#endif
