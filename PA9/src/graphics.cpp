#include "graphics.h"
#include <vector>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

Graphics::Graphics( btDiscreteDynamicsWorld* DynamicsWorld )
{
 dynamicsWorld = DynamicsWorld;
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
  string gouraud[ 2 ];
  string phong[ 2 ];
  
  gouraud[ 0 ] = "v_pVertex.glsl";
  gouraud[ 1 ] = "v_pVertex.glsl";
  
  phong[ 0 ] = "v_pFrag.glsl";
  phong[ 1 ] = "f_pFrag.glsl";
  
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

  // Load the models
  string objFile = "board.obj";
  m_ground = new Ground( objFile, dynamicsWorld );

  objFile = "sphere.obj";
  m_sphere = new Sphere( objFile, dynamicsWorld );

  objFile = "cylinder.obj";
  m_cylinder = new Cylinder( objFile, dynamicsWorld );

  objFile = "cube.obj";
  m_cube = new Cube( objFile, dynamicsWorld );
  
  m_walls = new Walls( dynamicsWorld );

  // Set up the shaders
  m_shaderGouraud = new Shader( gouraud );
  if(!m_shaderGouraud->Initialize( ))
  {
    printf("Gouraud Shader Failed to Initialize\n");
    return false;
  }

  // Set up the shaders
  m_shaderPhong = new Shader( phong );
  if(!m_shaderPhong->Initialize())
  {
    printf("Phong Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shaders
  if(!m_shaderGouraud->AddShader(GL_VERTEX_SHADER))
  {
    printf("Gouraud Vertex Shader failed to Initialize\n");
    return false;
  }

  if(!m_shaderPhong->AddShader(GL_VERTEX_SHADER))
  {
    printf("Phong Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shaders
  if(!m_shaderGouraud->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Gouraud Fragment Shader failed to Initialize\n");
    return false;
  }

  if(!m_shaderPhong->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Phong Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the programs
  if(!m_shaderGouraud->Finalize())
  {
    printf("Gouraud Program to Finalize\n");
    return false;
  }

  if(!m_shaderPhong->Finalize())
  {
    printf("Phong Program to Finalize\n");
    return false;
  }

  // Get matrices for active shader
  if( fNames[ 0 ] == "gouraud" || fNames[ 0 ] == "Gouraud" )
     {
      m_shader = m_shaderGouraud;
     }
  else
     {
      m_shader = m_shaderPhong;
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
    
  // Initialize lights
  Light spotlight;
  spotlight.LightPosition = glm::vec4(-4,0,10,1);
  spotlight.AmbientProduct = glm::vec4(0.0,0.0,0.0,0.0); 
  spotlight.DiffuseProduct = glm::vec4(0.4,0.3,0.1,1.0); 
  spotlight.SpecularProduct = glm::vec4(0.4,0.3,0.1,1.0); 
  spotlight.attenuation = 0.1f;
  spotlight.coneAngle = 15.0f;
  spotlight.coneDirection = glm::vec3(0,0,-1);

  Light directionalLight;
  directionalLight.LightPosition = glm::vec4(1, 0.8, 0.6, 0); 
  directionalLight.AmbientProduct = glm::vec4(0.2,0.2,0.2,1.0); 
  directionalLight.DiffuseProduct = glm::vec4(0.4,0.3,0.1,1.0); 
  directionalLight.SpecularProduct = glm::vec4(0.4,0.3,0.1,1.0); 

  lights.push_back(spotlight);
  lights.push_back(directionalLight);
 
  return true;
}

void Graphics::Update(unsigned int dt, string motion)
{
  double dTime = (double) dt / 1000;
  
  // Update the dynamics world
  dynamicsWorld->stepSimulation( dt, 1 );
  
  // Update the objects
  m_ground->Update( dynamicsWorld, dt );
  m_sphere->Update( dynamicsWorld, dt );
  m_cylinder->Update( dynamicsWorld, dt );
  m_cube->Update( dynamicsWorld, motion );
  
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();
  
  // Set uniforms for all lights
  setLightingUniforms();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the objects
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ground->getModel()));
  m_ground->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sphere->getModel()));
  m_sphere->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->getModel()));
  m_cylinder->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->getModel()));
  m_cube->Draw();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::setLightingUniforms()
   {
    // Set number of lights
    GLuint loc = m_shader->GetUniformLocation( "numLights" );
    int numLights = lights.size();
    glUniform1i( loc, numLights );

    for( int index = 0; index < lights.size(); index++ )
       {
        loc = m_shader->GetUniformLocation( "lights[ index ].LightPosition" );
        glUniform3fv( loc, 1, glm::value_ptr( lights[ index ].LightPosition ) );

        loc = m_shader->GetUniformLocation( "lights[ index ].AmbientProduct" );
        glUniform3fv( loc, 1, glm::value_ptr( lights[ index ].AmbientProduct ) );

        loc = m_shader->GetUniformLocation( "lights[ index ].DiffuseProduct" );
        glUniform3fv( loc, 1, glm::value_ptr( lights[ index ].DiffuseProduct ) );

        loc = m_shader->GetUniformLocation( "lights[ index ].SpecularProduct" );
        glUniform3fv( loc, 1, glm::value_ptr( lights[ index ].SpecularProduct ) );

        loc = m_shader->GetUniformLocation( "lights[ index ].coneAngle" );
        glUniform1f( loc, lights[ index ].coneAngle );

        loc = m_shader->GetUniformLocation( "lights[ index ].coneDirection" );
        glUniform3fv( loc, 1, glm::value_ptr( lights[ index ].coneDirection ) );

        loc = m_shader->GetUniformLocation( "lights[ index ].attenuation" );
        glUniform1f( loc, lights[ index ].attenuation );
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

