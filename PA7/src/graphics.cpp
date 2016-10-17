#include "graphics.h"
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

Graphics::Graphics()
{
    planets.resize(10);
}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height, std::string fNames[] )
{
  // Initialize function/variables
  bool validObj;
  
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
         
  // Load models for solar system
  loadPlanets();

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

void Graphics::loadPlanets()
   {
    // initialize function/variables
    int index;
    
    // Loop through sun, planets, and pluto
    for( index = 0; index < 10; index++ )
       {
        // Check planet index
        switch( index )
           {
            // Check for sun index
            case 0:
              planets[ index ] = new Planet( index, "sun.obj", 1.0, 26.24, 0, 0, -1  ); 
              break;  
  
            // Check for mercury index
            case 1:
              planets[ index ] = new Planet( index, "mercury.obj", 0.0056, 58.65, 0, 0.39, .24 ); 
              break;  

            // Check for venus index
            case 2:
              planets[ index ] = new Planet( index, "venus.obj", 0.0143, 243, 0, 0.72, 0.62 ); 
              break;

            // Check for earth index
            case 3:
              planets[ index ] = new Planet( index, "earth.obj", 0.0151, 1, 1, 1, 1 ); 
              break;  
            
            // Check for mars index
            case 4:
              planets[ index ] = new Planet( index, "mars.obj", 0.008, 1.03, 2, 1.52, 1.88 ); 
              break;

            // Check for jupiter index
            case 5:
              planets[ index ] = new Planet( index, "jupiter.obj", 0.1652, 0.41, 67, 5.2, 11.86 ); 
              break;  
  
            // Check for saturn index
            case 6:
              planets[ index ] = new Planet( index, "saturn.obj", 0.1388, 0.44, 62, 9.54, 29.46 ); 
              break;  

            // Check for uranus index
            case 7:
              planets[ index ] = new Planet( index, "uranus.obj", 0.0591, 0.72, 27, 19.18, 84.01 ); 
              break;

            // Check for neptune index
            case 8:
              planets[ index ] = new Planet( index, "neptune.obj", 0.0573, 0.72, 14, 30.06, 164.8 ); 
              break;  
            
            // Otherwise, assume pluto index
            default:
              planets[ index ] = new Planet( index, "pluto.obj", 0.0027, 6.38, 5, 39.44, 247.7 ); 
              break;
           }
       
       }
   }

void Graphics::Update(unsigned int dt)
{
  // Initialize function/variables
  int index;
  
  // Loop through all objects in system
  for( index = 0; index < 10; index++ )
     {
      // Update the current object
      planets[ index ]->Update(dt);
     }
}

void Graphics::Render()
{
  // Initialize function/variables
  int index;
  
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Loop through all objects in the system
  for( index = 0; index < 10; index++ )
     {
      // Render the current object
      glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(planets[index]->getModel()));
      planets[ index ]->Draw( m_modelMatrix );
     }
  // end loop

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
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

