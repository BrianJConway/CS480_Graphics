#ifndef MOON_H
#define MOON_H

#include <vector>
using namespace std;

#include "graphics_headers.h"
#include "object.h"
#include "planet.h"

class Moon : public Object
{
  public:
    Moon( Planet* planet );
    ~Moon();
    void Update(unsigned int dt, vector<string> motionSettings);
    void Render();

    glm::mat4 GetModel();

  private:
    Planet* planet;
};

#endif /* MOON_H */
