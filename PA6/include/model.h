#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
   {
    public:
        Model(string file);
        void Draw();	
		void Update(unsigned int dt);
		glm::mat4 getModel();

    private:
        void loadModel();
        void processNode( aiNode* node, const aiScene* scene );
        Mesh processMesh( aiMesh* mesh, const aiScene* scene );
        vector<Gluint> loadMaterialTextures( aiMaterial* material )
        GLuint loadTexture( string fileName );
        
        vector<Mesh> meshes;
        string path;
		glm::mat4 model;
		float rotateAngle;

   };
   
#endif
