#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include "graphics_headers.h"
//#include "moon.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Planet: public Model
{
        
    public:
        // Constructor
        Planet(float radius, float speed, int moons, bool saturn, string fileName);

        // Destructor
        ~Planet();

        void Update(unsigned int dt);
        void Draw(GLint modelMatrix);

    private:
        //vector<Moon> Moons;

        float Radius;
        float Speed;
        int NumMoons;
        bool IsSaturn;
};

#endif
