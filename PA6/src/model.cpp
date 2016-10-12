#include "model.h"
#include "SOIL.h"
#include <iostream>

using namespace std;

// Constructor
Model::Model(string file)
   {
    file = "models/" + file;
    path = file;
    this->loadModel();
   }

// Draws the model by drawing each mesh
void Model::Draw()
   {
    for(GLuint index = 0; index < this->meshes.size(); index++)
       {
        this->meshes[ index ].Draw();
       }
   }
    
// Slowly moves the model
void Model::Update(unsigned int dt)
   {
    rotateAngle += dt * M_PI/9000;

    model = glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 1.0, 0.0));
   } 

// Uses ASSIMP to load the model from the file
void Model::loadModel()
   {
    // Read file info into aiScene object
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
    for(GLuint index = 0; index < node->mNumMeshes; index++)
       {
        // Get the mesh based on the index kept by the node, push to vector
        aiMesh* mesh = scene->mMeshes[node->mMeshes[ index ]]; 
        this->meshes.push_back(this->processMesh(mesh, scene));			
       }
       
    // If child nodes exist, process them as well
    for(GLuint index = 0; index < node->mNumChildren; index++)
       {
        this->processNode(node->mChildren[ index ], scene);
       }
   }

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
   {
    // Vertex and index vectors
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<GLuint> textures;
    
    glm::vec2 vec;
    glm::vec3 vector; 
    Vertex vertex;

    // Iterate throgh all the vertices of the mesh
    for(GLuint index = 0; index < mesh->mNumVertices; index++)
       {
        // Vertex coordinates
        vector.x = mesh->mVertices[ index ].x;
        vector.y = mesh->mVertices[ index ].y;
        vector.z = mesh->mVertices[ index ].z;
        vertex.vertex = vector;
            
        if(mesh->mTextureCoords[0])
           {
            vec.x = mesh->mTextureCoords[0][ index ].x; 
            vec.y = mesh->mTextureCoords[0][ index ].y;
            vertex.texCoords = vec;
           }
        else
           {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
           }   
            
        vertices.push_back(vertex);
       }

    // Iterate through faces of the mesh
    for(GLuint meshIndex = 0; meshIndex < mesh->mNumFaces; meshIndex++)
       {
        aiFace face = mesh->mFaces[ meshIndex ];

        // Get the indices associated with the current face
        for(GLuint index = 0; index < face.mNumIndices; index++)
           {
            indices.push_back( face.mIndices[ index ] );
           }
       }

    // Process materials of the mesh
    if(mesh->mMaterialIndex >= 0)
       {
        // Get current material
        aiMaterial* material = scene->mMaterials[ mesh->mMaterialIndex ];
        
        // Load textures for current material
        textures = loadMaterialTextures( material );
       }
        
    // Return data obtained from loaded mesh
    return Mesh(vertices, indices, textures );
   }
    
vector<GLuint> Model::loadMaterialTextures( aiMaterial* material )
   {
    // initialize function/variables
    vector<GLuint> textures;
    GLuint index; 
    aiString file;
    GLuint texture;
    
    // Loop through textures for each material
    for( index = 0; index < material->GetTextureCount( aiTextureType_DIFFUSE ); index++ )
       {
        // Get filename of texture
        material->GetTexture( aiTextureType_DIFFUSE, index, &file );
        
        // use SOIL to load texture
        texture = loadTexture( file );
        
        // Add texture to vector
        textures.push_back( texture );
       }
    // end loop
    
    // Return texture vector
    return textures;
   }
   
GLuint Model::loadTexture( aiString fileName )
   {
    // initialize function/variables
    int height, width;
    GLuint texture;
    unsigned char* img;
    
    fileName = "models/" + string( fileName.C_Str() );
    
    
    cout << fileName.C_Str() << endl;
    
    glGenTextures(1, &texture );
    img = SOIL_load_image( fileName.C_Str(), &width, &height, 0, SOIL_LOAD_RGB );

    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);	
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(img);
    
    return texture;
   }
   
// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
