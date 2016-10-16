#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include "graphics_headers.h"
#include "moon.h"
#include "model.h"

using namespace std;

// Derived from Model Class
class Planet: private Model
{
    public:
        // Constructor
        Planet(float radius, float speed, int moons, bool saturn);

        // Destructor
        ~Planet();

        void Update(unsigned int dt);
        void Draw();

    private:
        vector<Moon> Moons;

        float Radius;
        float Speed;
        int NumMoons;
        bool IsSaturn;
};

#endif
