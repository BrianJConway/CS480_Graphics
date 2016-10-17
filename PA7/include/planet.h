#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include "graphics_headers.h"
//#include "moon.h"
#include "model.h"

using namespace std;

// Derived from Model Class
class Planet: private Model
{
    public:
        // Constructor
        Planet(int index, string fileName, float radius, float speed, int moons, float distanceFromSun, float orbitPeriod);

        // Destructor
        ~Planet();

        void Update(unsigned int dt);
        void Draw(GLint modelMatrix);
        glm::mat4 getModel();

    private:
        //vector<Moon> Moons;

        float Radius;
        float Speed;
        int NumMoons;
};

#endif
