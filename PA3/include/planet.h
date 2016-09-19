#ifndef PLANET_H
#define PLANET_H

#include <vector>
using namespace std;

#include "graphics_headers.h"
#include "object.h"

class Planet : public Object
{
  public:
    Planet();
    ~Planet();
    void Update(unsigned int dt, vector<string> motionSettings);
    void Render();

    glm::mat4 GetModel();

  private:

};

#endif /* PLANET_H */
