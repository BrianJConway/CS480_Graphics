#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
   {
    public:
        Model(string path);
        void Draw();	
		void Update(unsigned int dt);
		glm::mat4 getModel();

    private:
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        
        vector<Mesh> meshes;
        string directory;
		glm::mat4 model;
		float rotateAngle;

   };
   
#endif
