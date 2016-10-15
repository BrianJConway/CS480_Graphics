#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
   {
    public:
        Model( string file );
        void Draw();	
		virtual void Update(unsigned int dt) = 0;
		glm::mat4 getModel();

    protected:
        Mesh mesh;
		glm::mat4 model;
   };
   
#endif
