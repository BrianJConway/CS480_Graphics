#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
{
    public:
        /*  Functions   */
        Model(string path);
        void Draw();	
		void Update(unsigned int dt);
		glm::mat4 getModel();

    private:
        /*  Model Data  */
        vector<Mesh> meshes;
        string directory;
		glm::mat4 model;
		float rotateAngle;

        /*  Functions   */
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        //vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, 
                                            // string typeName);


};
