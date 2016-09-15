#ifndef SHADER_H
#define SHADER_H

#include <vector>
using namespace std;

#include "graphics_headers.h"

class Shader
{
  public:
    Shader( std::string fileNames[] );
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
    
    // Holds filenames for vertex and fragment shaders
    // Vertex shader filename in first element
    // Fragment shader filename in second element
    string shaderFiles[ 2 ];
};

#endif  /* SHADER_H */
