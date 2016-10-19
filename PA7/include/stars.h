#ifndef STARS_H
#define STARS_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"

using namespace std;

// Derived from Model Class
class Stars: public Model
{
    public:
        // Constructor
        Stars();

        // Destructor
        ~Stars();

        void Update(unsigned int dt);
        void Draw(GLint modelMatrix);
        glm::mat4 getModel();

    private:
};

#endif
