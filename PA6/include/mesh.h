#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"

using namespace std;

class Mesh
   {
    public:
        // Constructor
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<GLuint> textures);

        void Draw();
        
    private:
        // Data
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<GLuint> textures;
        GLuint VAO, VBO, IBO;
   };

#endif 
