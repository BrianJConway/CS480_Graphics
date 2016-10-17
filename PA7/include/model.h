#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
   {
    public:
        Model();
        Model( string file );
        virtual void Draw(GLint modelMatrix) = 0;	
		virtual void Update(unsigned int dt) = 0;
		glm::mat4 getModel();

    protected:
        Mesh mesh;
		glm::mat4 model;
        float rotateAngle;
   };
   
#endif
