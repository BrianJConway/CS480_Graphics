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
        Planet(int index, string fileName, double RelativeSize, double RotateSpeed, int moons, double OrbitDistance, double OrbitPeriod, bool realistic );

        // Destructor
        ~Planet();

        void Update(unsigned int dt);
        void Draw(GLint modelMatrix);
        glm::mat4 getModel();

    private:
        //vector<Moon> Moons;
        
        int planetIndex, numMoons;
        double relativeSize, rotateSpeed, orbitDistance, orbitPeriod;
        float rotateAngle, orbitAngle;
        bool realistic;
};

#endif
