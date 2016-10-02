#include "graphics_headers.h"
#include "mesh.h"

class Model 
{
    public:
        /*  Functions   */
        Model(GLchar* path);
        void Draw();	
		void Update(unsigned int dt);

    private:
        /*  Model Data  */
        vector<Mesh> meshes;
        string directory;
		glm::mat4 model;

        /*  Functions   */
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, 
                                             string typeName);
};
