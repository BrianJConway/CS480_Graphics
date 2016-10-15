#include "model.h"
#include "SOIL.h"
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

// Constructor
Model::Model(string file)
   {
    path = "models/" + file;
    
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

    glm:: mat4 scale, rotate;
    
    //scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f));
    rotate = glm::rotate(glm::mat4(1.0f), (rotateAngle), glm::vec3(0.0, 1.0, 0.0));
    
    model = rotate * scale;
   } 

// Uses ASSIMP to load the model from the file
void Model::loadModel()
   {
    // Read file info into aiScene object
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices );

    // Check for errors in file input
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
       {
        cout << "ASSIMP ERROR: " << importer.GetErrorString() << endl;
        return;
       }
       
    // Process ASSIMP nodes of aiScene object
    this->processScene( scene );
   }

// Recursively process the meshes of each node
void Model::processScene( const aiScene* scene )
   {
    int numMeshes = scene->mNumMeshes;
    
    // Process all meshes of the current node
    for(GLuint index = 0; index < numMeshes; index++)
       {
        // Get the mesh based on the index kept by the node, push to vector
        aiMesh* mesh = scene->mMeshes[ index ]; 
        this->meshes.push_back(this->processMesh(mesh, scene));			
       }
   }

Mesh Model::processMesh( aiMesh* mesh, const aiScene* scene )
   {
    // initialize variables    
    unsigned int matIndex = mesh->mMaterialIndex;
    int texIndex;
    
    // Vertex and index vectors
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture*> textures;
    
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
    for( texIndex = 0; texIndex < scene->mNumMaterials; texIndex++ )
       {
        // Get current material
        aiMaterial* material = scene->mMaterials[ texIndex ];
   
        if( mesh->mMaterialIndex == texIndex )
           {
            // Load textures for current material
            textures = loadMaterialTextures( material );           
           }
       }

    // Return data obtained from loaded mesh
    return Mesh(vertices, indices, textures, matIndex );
   }
    
vector<Texture*> Model::loadMaterialTextures( aiMaterial* material )
   {
    // initialize function/variables
    vector<Texture*> textures;
    Texture * texture = NULL;
    GLuint index; 
    aiString file;
    
    // Loop through textures for each material
    for( index = 0; index < material->GetTextureCount( aiTextureType_DIFFUSE ); index++ )
       {
        // Get filename of texture
        material->GetTexture( aiTextureType_DIFFUSE, index, &file );
        
        cout << file.C_Str() << endl;
        
        // use Imagemagick to load texture
        texture = new Texture( GL_TEXTURE_2D, file.C_Str() );
        
        
        if( ! ( texture->Load() ) )
           {
            cout << "Error loading texture" << endl;
            delete texture;
            texture = NULL;
           }

        // Add texture to vector
        textures.push_back( texture );
       }
    // end loop

    // Return texture vector
    return textures;
   }
   
// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
