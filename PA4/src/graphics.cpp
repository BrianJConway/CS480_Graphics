#include "graphics.h"
#include <vector>
#include <fstream>

using namespace std;

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height, std::string fNames[] )
{
  // Initialize function/variables
  bool validObj;
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Load the object data from a file
  validObj = loadObj( fNames[ 2 ], vertices, indices );
  
  // Check if invalid object data or filename
  if( !validObj )
     {
      printf("Object failed to Initialize\n");
      return false;
     }
     
  // Create the object   
  m_cube = new Object( vertices, indices );

  // Set up the shaders
  m_shader = new Shader( fNames );
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  // Update the object
  m_cube->Update(dt);
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the object
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  m_cube->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

bool Graphics::loadObj(string fileName, vector<Vertex> Vertices, 
                                                 vector<unsigned int> Indices )
   {
    // Initialize function/variables
    int index;
    float tempI;
    char dummy;
    glm::vec3 tempV;
    glm::vec3 color = glm::vec3( 1.0, 1.0, 1.0 );

    bool result = false;
    ifstream fin;
    string label;
    
    // Clear and open input file
    fin.clear();
    fin.open( "objects/" + fileName );
    
    // Check if input file opened correctly
    if( fin.good() )
       {
        // Indicate valid object input so far
        result = true;
        
        // Loop through input file
        while( fin.good() )
           {
            // Get beginning word of line
            fin >> label;
            
            // Check beginning of line for vertex
            if( label == "v" )
               {
                // Read in vertex coordinates
                fin >> tempV.x;
                fin >> tempV.y;
                fin >> tempV.z;
                
                // Set Vertex values
                Vertex tempVertex( tempV, color );
                    
                // Add to vertex vector
                Vertices.push_back( tempVertex );
                   
               }
            // Check beginning of line face
            else if( label == "f" )
               {
                // Read in indices
                for( index = 0; index < 3; index++ )
                   {
                    // Read current index
                    fin >> tempI;
                    
                    // Read in-between characters
                    fin >> dummy >> dummy >> dummy;
                    
                    // Add to index vector
                    Indices.push_back( tempI );
                   }
               }
            // Otherwise, assume not vertex or face
            else
               {
                // Ignore line
                fin.ignore( 30, '\n' );
               }
           }
        // end loop
        
        // Close input file
        fin.close();
       }

    // Return whether object loaded correctly
    return result;
   }

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

