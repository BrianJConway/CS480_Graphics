#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include "shader.h"

#include <string>

using namespace std;

class Model 
   {
    public:
        Model(string file);
        void Draw(Shader shader);	
		void Update(unsigned int dt);
		glm::mat4 getModel();

    private:
        void loadModel();
        void processNode( aiNode* node, const aiScene* scene );
        Mesh processMesh( aiMesh* mesh, const aiScene* scene );
        vector<GLuint> loadMaterialTextures( aiMaterial* material );
        GLuint loadTexture( aiString fileName );
        
        vector<Mesh> meshes;
        string path;
		glm::mat4 model;
		float rotateAngle;

   };
   
#endif
