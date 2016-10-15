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
		void Update(unsigned int dt);
		glm::mat4 getModel();

    private:
        Mesh mesh;
		glm::mat4 model;
		float rotateAngle;

   };
   
#endif
