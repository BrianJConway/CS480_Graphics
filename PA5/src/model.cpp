#include "model.h"
#include <time.h>

// Constructor
Model::Model(string path)
   {
    this->loadModel(path);
   }

// Draws the model by drawing each mesh
void Model::Draw()
   {
    for(GLuint i = 0; i < this->meshes.size(); i++)
       {
        this->meshes[i].Draw();
       }
   }
    
// Slowly moves the model
void Model::Update(unsigned int dt)
   {
    rotateAngle += dt * M_PI/9000;

    model = glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 1.0, 0.0));
   } 

// Uses ASSIMP to load the model from the file
void Model::loadModel(string path)
   {
    // Read file info into aiScene object
    path = "models/" + path;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Check for errors in file input
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
       {
        cout << "ASSIMP ERROR: " << importer.GetErrorString() << endl;
        return;
       }
       
    // Process ASSIMP nodes of aiScene object
    this->processNode(scene->mRootNode, scene);
   }

// Recursively process the meshes of each node
void Model::processNode(aiNode* node, const aiScene* scene)
   {
    // Process all meshes of the current node
    for(GLuint i = 0; i < node->mNumMeshes; i++)
       {
        // Get the mesh based on the index kept by the node, push to vector
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        this->meshes.push_back(this->processMesh(mesh, scene));			
       }
       
    // If child nodes exist, process them as well
    for(GLuint i = 0; i < node->mNumChildren; i++)
       {
        this->processNode(node->mChildren[i], scene);
       }
   }

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
   {
    // Vertex and index vectors
    vector<Vertex> vertices;
    vector<GLuint> indices;
          
    srand(time(NULL));

    // Iterate throgh all the vertices of the mesh
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
       {
        Vertex vertex;
        glm::vec3 vector; 
            
        // Vertex coordinates
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.vertex = vector;
            
        // Set random color for each vertex
        vector.x = (float) rand() / (float) RAND_MAX;
        vector.y = (float) rand() / (float) RAND_MAX;
        vector.z = (float) rand() / (float) RAND_MAX;
        vertex.color = vector;
            
        vertices.push_back(vertex);
       }

    // Iterate through faces of the mesh
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
       {
        aiFace face = mesh->mFaces[i];

        // Get the indices associated with the current face
        for(GLuint j = 0; j < face.mNumIndices; j++)
           {
            indices.push_back(face.mIndices[j]);
           }
       }

    // Process materials of the mesh
    if(mesh->mMaterialIndex >= 0)
       {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
       }
        
    // Return data obtained from loaded mesh
    return Mesh(vertices, indices );
   }
    
// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
