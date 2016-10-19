#ifndef MOON_H
#define MOON_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"

using namespace std;

// Derived from Model Class
class Moon: public Model
{
    public:
        // Constructor
        Moon(int index, string fileName); 

        // Destructor
        ~Moon();

        void Update(unsigned int dt);
        void Draw(GLint modelMatrix);
        glm::mat4 getModel();
        void UpdatePlanet(glm::mat4 model);

    private:
        glm::mat4 planetModel;
	int Index;
	float orbitAngle;
};

#endif
