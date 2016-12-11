#include "graphics.h"
#include <vector>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

bool Sphere::launched = false;
bool Sphere::passed = false;
int Sphere::launchCount = 0;

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
  gouraud[ 1 ] = "f_pVertex.glsl";
  
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
  
  m_ground = new Ground( -1, dynamicsWorld );
  m_ceiling = new Ground( 200, dynamicsWorld );
  
  string objFile = "Bed.obj";
  m_room = new Room(objFile, dynamicsWorld);

  objFile = "Table.obj";
  m_table1 = new Table1(objFile, dynamicsWorld);

  objFile = "Table2.obj";
  m_table2 = new Table2(objFile, dynamicsWorld);
  
  objFile = "Table.obj";
  m_table3 = new Table3(objFile, dynamicsWorld);

  objFile = "Table.obj";
  m_table4 = new Table4(objFile, dynamicsWorld);
  
  objFile = "baseball.obj";  
  m_sphere = new Sphere(objFile, dynamicsWorld, 81.6, 80, 92 );
  spheres.push_back( m_sphere );
//  m_sphere = new Sphere(objFile, dynamicsWorld, 59, 146, 395 );
//  spheres.push_back( m_sphere );
  m_sphere = new Sphere(objFile, dynamicsWorld, 68, 61, 160 );
  spheres.push_back( m_sphere );
  m_sphere = new Sphere(objFile, dynamicsWorld, 81, 61, 215 );
  spheres.push_back( m_sphere );
  
  objFile = "cannon.obj";
  m_cannon = new Cannon( objFile, dynamicsWorld );

  objFile = "ramp.obj";
  m_ramp = new Ramp(objFile, dynamicsWorld);

  objFile = "Domino90.obj";
  for( int index = 0; index < 53; index++ )
     {
       m_domino1 = new Domino(objFile, dynamicsWorld, 81, 61, 113 + ( 1.9 * (float) index ), 0 );
       
       dominos.push_back( m_domino1 );
     }

/*
  for( int index = 0; index < 15; index++ )
     {
       objFile = "Domino.obj";
       m_domino1 = new Domino(objFile, dynamicsWorld, 69.5 - ( 1.9 * (float) index ), 60, 160, -90 );
       
       dominos.push_back( m_domino1 );
     }
*/
     
     objFile = "rampLeft.obj";
//     m_rampThing1 = new RampThing(objFile, dynamicsWorld, "left" );

     objFile = "rampRight.obj";
//     m_rampThing2 = new RampThing(objFile, dynamicsWorld, "right" );

     objFile = "spiral.obj";
     m_spiral = new Spiral(objFile, dynamicsWorld);

    objFile = "Sugar.obj";
  m_sugar = new Sugar(objFile, dynamicsWorld);

  objFile = "Coffee.obj";
  m_cup = new Cup(objFile, dynamicsWorld);
  
  objFile = "Pencil.obj";
  m_pencil = new Pencil(objFile, dynamicsWorld);

  objFile = "Trepezoidal.obj";
  m_trapezoid = new Trapezoid(objFile, dynamicsWorld);

  objFile = "Board.obj";
  m_board = new Board(objFile, dynamicsWorld);

  objFile = "woodBlock.obj";
  for(int index = 0; index < 2; index++)
  {
        objFile = "woodBlock.obj";
        m_block = new Block(objFile, dynamicsWorld, -76, 29.2 + ( 5 * (float) index ), 172.5, 0 );
       
       blocks.push_back( m_block ); 
  }

  for(int index = 0; index < 2; index++)
  {
        objFile = "woodBlock.obj";
        m_block = new Block(objFile, dynamicsWorld, -73, 29.2 + ( 5 * (float) index ), 172.5, 0 );
       
       blocks.push_back( m_block ); 
  }

  for(int index = 0; index < 1; index++)
  {
        objFile = "woodBlock.obj";
        m_block = new Block(objFile, dynamicsWorld, -74.5, 29.2 + ( 3 * (float) index ), 173.7, 90 );
       
       blocks.push_back( m_block ); 
  }

  for(int index = 0; index < 1; index++)
  {
        objFile = "woodBlock.obj";
        m_block = new Block(objFile, dynamicsWorld, -74.5, 29.2 + ( 3 * (float) index ), 171.3, 90 );
       
       blocks.push_back( m_block ); 
  }

  for(int index = 0; index < 25; index++)
  {
        objFile = "Domino90.obj";
        m_domino3 = new Domino(objFile, dynamicsWorld, -68.6, 48.6, 283 + ( 1.9 * (float) index ), 0 );
       
       dominos3.push_back( m_domino3 ); 
  }

  for(int index = 0; index < 3; index++)
  {
        objFile = "Domino90.obj";
        m_domino3 = new Domino(objFile, dynamicsWorld, -68.6 + index, 48.6, 330 + ( 1.9 * (float) index ), 45 );
       
       dominos3.push_back( m_domino3 ); 
  }

  for(int index = 0; index < 10; index++)
  {
        objFile = "Domino90.obj";
        m_domino3 = new Domino(objFile, dynamicsWorld, -65 + (1.9 * (float) index), 48.4, 335, 90 );
       
       dominos3.push_back( m_domino3 ); 
  }
    

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

  // Start the correct program
  m_shader->Enable();
      
  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
    
  // Initialize lights
  Light light;
  light.LightPosition = glm::vec4( 0.1,10.0,-0.1,0.0);
  light.AmbientProduct = glm::vec4(0.2,0.2,0.2,1.0); 
  light.DiffuseProduct = glm::vec4(0.1,0.1,0.9,1.0); 
  light.SpecularProduct = glm::vec4(0.9,0.1,0.1,1.0); 
  light.coneAngle = 180.0;
  light.coneDirection = glm::vec3( 0.0, -1.0, 0.0 );
  light.brightness = 1.0;

  Light light2;
  light2.LightPosition = glm::vec4( 0.5,10.0,-1.5,1.0);
  light2.AmbientProduct = glm::vec4(0.1,0.1,0.1,1.0); 
  light2.DiffuseProduct = glm::vec4(0.4,0.4,0.4,1.0); 
  light2.SpecularProduct = glm::vec4(0.6,0.6,0.6,1.0); 
  light2.coneAngle = 10.0;
  light2.coneDirection = glm::vec3( 0.0, -1.0, -1.5 );
  light2.brightness = 1.0;
  
  
  lights.push_back(light2);
  lights.push_back(light);
 
  return true;
}

void Graphics::Update(unsigned int dt, string motion[])
{
  
  // Check for shader swap
  if( motion[ 1 ] == "GOURAUD" || motion[ 1 ] == "PHONG" )
     {
      swapShaders( motion[ 1 ] );
     }
  else if( motion[ 1 ] != "NONE" )
     {
      adjustLighting( motion[ 1 ] );
     }
  if( motion[0] == "UP")
     {

     }
  if( motion[0] == "RIGHT")
     {

     }
  if( motion[0] == "LEFT")
     {


     }
     
  double dTime = (double) dt / 500;

  // Update the dynamics world
  dynamicsWorld->stepSimulation( dTime, 1 );
  
  // Update the objects
  m_room->Update(dynamicsWorld, dt);
  m_table1->Update(dynamicsWorld, dt);
  m_table2->Update(dynamicsWorld, dt);  
  m_table3->Update(dynamicsWorld, dt);
  m_table4->Update(dynamicsWorld, dt);

  if( Sphere::launched && !(Sphere::passed) )
     {
      Sphere::launchCount++;
      

      if( Sphere::launchCount % 3000 == 0 )
         {
          string objFile = "baseball.obj";
          m_sphere = new Sphere(objFile, dynamicsWorld, 81.5, 50.7, 223 );
          spheres.push_back( m_sphere );
         }

     }

  for( int index = 0; index < spheres.size(); index++ )
     {
      spheres[ index ]->Update( dynamicsWorld, dt );
     }
     
  m_ramp->Update(dynamicsWorld, dt);
  m_cannon->Update(dynamicsWorld, dt);

  for( int index = 0; index < dominos.size(); index++ )
     {
      dominos[ index ]->Update( dynamicsWorld, dt );
     }

//  m_rampThing1->Update(dynamicsWorld, dt);     
//  m_rampThing2->Update(dynamicsWorld, dt);     
  m_spiral->Update(dynamicsWorld, dt);

  m_sugar->Update(dynamicsWorld, dt);
  m_cup->Update(dynamicsWorld, dt);
  m_pencil->Update(dynamicsWorld, dt);
  m_trapezoid->Update(dynamicsWorld, dt);
  m_board->Update(dynamicsWorld, dt);

  for(unsigned int index = 0; index < dominos3.size(); index++ )
     {
      dominos3[ index ]->Update( dynamicsWorld, dt );
     }
  for(unsigned int index = 0; index < blocks.size(); index++ )
     {
      blocks[ index ]->Update( dynamicsWorld, dt );
     }

}

void Graphics::swapShaders( string shader )
   {
    if( shader == "PHONG" )
       {
        m_shader = m_shaderPhong;
       }
    else if( shader == "GOURAUD" )
       {
        m_shader = m_shaderGouraud;
       }   

    m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
    m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
    m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");

    // Start the correct program
    m_shader->Enable();
   }
   

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the objects
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_room->getModel()));
  setLightingUniforms( m_room );
  m_room->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_table1->getModel()));
  setLightingUniforms( m_table1 );
  m_table1->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_table2->getModel()));
  setLightingUniforms( m_table2 );
  m_table2->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_table3->getModel()));
  setLightingUniforms( m_table3 );
  m_table3->Draw();
    
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_table4->getModel()));
  setLightingUniforms( m_table4 );
  m_table4->Draw();

  for( int index = 0; index < spheres.size(); index++ )
     {
      glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(spheres[index]->getModel()));
      setLightingUniforms( spheres[index] );
      spheres[index]->Draw();
     }


  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ramp->getModel()));
  setLightingUniforms( m_ramp );
  m_ramp->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cannon->getModel()));
  setLightingUniforms( m_cannon );
  m_cannon->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_domino1->getModel()));
  setLightingUniforms( m_domino1 );
  m_domino1->Draw();
  

  for( int index = 0; index < dominos.size(); index++ )
     {
      glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(dominos[index]->getModel()));
      setLightingUniforms( dominos[ index ] );
      dominos[ index ]->Draw();
     }


  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_spiral->getModel()));
  setLightingUniforms( m_spiral );
  m_spiral->Draw();

/*
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_rampThing1->getModel()));
  setLightingUniforms( m_rampThing1 );
  m_rampThing1->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_rampThing2->getModel()));
  setLightingUniforms( m_rampThing2 );
  m_rampThing2->Draw();
*/

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_domino3->getModel()));
  setLightingUniforms( m_domino3 );
  m_domino3->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_block->getModel()));
  setLightingUniforms( m_block );
  m_block->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sugar->getModel()));
  setLightingUniforms( m_sugar );
  m_sugar->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cup->getModel()));
  setLightingUniforms( m_cup );
  m_cup->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_pencil->getModel()));
  setLightingUniforms( m_pencil );
  m_pencil->Draw();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_trapezoid->getModel()));
  setLightingUniforms( m_trapezoid );
  m_trapezoid->Draw();
 
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_board->getModel()));
  setLightingUniforms( m_board );
  m_board->Draw();

  for(unsigned int index = 0; index < dominos3.size(); index++ )
     {
      glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(dominos3[index]->getModel()));
      setLightingUniforms( dominos3[ index ] );
      dominos3[ index ]->Draw();
     }

  for(unsigned int index = 0; index < blocks.size(); index++ )
     {
      glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(blocks[index]->getModel()));
      setLightingUniforms( blocks[ index ] );
      blocks[ index ]->Draw();
     }

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::setLightingUniforms( Model* object )
   {
    // Set number of lights
    GLuint loc = m_shader->GetUniformLocation( "numLights" );
    int numLights = lights.size();
    glUniform1i( loc, numLights );
    string locName;

    loc = m_shader->GetUniformLocation( "Shininess" );
    glUniform1f( loc, object->getShininess() );

    for( int index = 0; index < lights.size(); index++ )
       {
        locName = "lights[" + to_string(index) + "].LightPosition";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform4fv( loc, 1, glm::value_ptr( lights[ index ].LightPosition ) );

        locName = "lights[" + to_string(index) + "].AmbientProduct";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform4fv( loc, 1, glm::value_ptr( lights[ index ].AmbientProduct ) );

        locName = "lights[" + to_string(index) + "].DiffuseProduct";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform4fv( loc, 1, glm::value_ptr( lights[ index ].DiffuseProduct ) );

        locName = "lights[" + to_string(index) + "].SpecularProduct";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform4fv( loc, 1, glm::value_ptr( lights[ index ].SpecularProduct ) );

        locName = "lights[" + to_string(index) + "].coneAngle";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform1f( loc, lights[ index ].coneAngle );
        
        locName = "lights[" + to_string(index) + "].coneDirection";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform3fv( loc, 1, glm::value_ptr( lights[ index ].coneDirection ) );

        locName = "lights[" + to_string(index) + "].brightness";
        loc = m_shader->GetUniformLocation( locName.c_str() );
        glUniform1f( loc, lights[ index ].brightness );
       }
   }

void Graphics::adjustLighting( string control )
   {
    int index;
    
    if( control == "I AMBIENT BRIGHT" )
       {
        lights[ 1 ].AmbientProduct += glm::vec4( -0.1, -0.1, -0.1, 0.0 );       
       }
    else if( control == "D AMBIENT BRIGHT" )
       {
        lights[ 1 ].AmbientProduct += glm::vec4( 0.1, 0.1, 0.1, 0.0 ); 
       }
    else if( control == "I SPEC" )
       {
        m_room->adjustShininess( "UP" );
       }
    else if( control == "D SPEC" )
       {
        m_room->adjustShininess( "DOWN" );
       }
    else if( control == "I SPOT SIZE" )
       {
        lights[ 0 ].coneAngle += 1;
       }
    else if( control == "D SPOT SIZE" )
       {
        lights[ 0 ].coneAngle -= 1;
       }
   }
    
btVector3 Graphics::getSphereCOM()
{

}

int Graphics::getBallNum()
{
    return BallNum;
}

int Graphics::getScore()
{
    return Score;
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

Camera* Graphics::getCamera()
   {
    return m_camera;
   }

