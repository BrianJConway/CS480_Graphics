#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"
#include "shader.h"
#include "texture.h"

using namespace std;

class Mesh
   {
    public:
        // Constructor
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture*> textures, unsigned int matIndex );

        void Draw();
        
    private:
        // Data
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<Texture*> textures;
        unsigned int materialIndex;
        GLuint VAO, VBO, IBO;
   };

#endif 
