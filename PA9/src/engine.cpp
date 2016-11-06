
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  delete m_dynamicsWorld;
  delete m_solver;
  delete m_dispatcher;
  delete m_collisionConfiguration;
  delete m_broadPhase;
  m_dynamicsWorld = NULL;
  m_solver = NULL;
  m_dispatcher = NULL;
  m_collisionConfiguration = NULL;
  m_broadPhase = NULL;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize( std::string fileNames[] )
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Initialize dynamics world

      // Broadphase algorithm checks which pairs of objects have collided
      m_broadPhase = new btDbvtBroadphase();
        
      // Collision config allows you to tune algorithms used for full collision detection
      m_collisionConfiguration = new btDefaultCollisionConfiguration();
                                              
      // Collision dispatcher can be used to register a callback that filters
      // overlapping broadphase proxies so that the collisions are not processed
      // by the rest of the system.
      m_dispatcher = new btCollisionDispatcher( m_collisionConfiguration );
        
      // Recognizes non-standard colision objects colliding
      btGImpactCollisionAlgorithm::registerAlgorithm( m_dispatcher );
        
      // Solver causes objects to interact properly based on gravity, forces,
      // collisions, and hinge constraints.
      m_solver = new btSequentialImpulseConstraintSolver;
        
      // Instantiate dynamics world
      m_dynamicsWorld = new btDiscreteDynamicsWorld( m_dispatcher, m_broadPhase,
                                           m_solver, m_collisionConfiguration );
                           
      // Set gravity, this sets Y axis as "up" and gravity pointing down
      m_dynamicsWorld->setGravity( btVector3( 0, -9.80, 0 ) );

  // Start the graphics
  m_graphics = new Graphics( m_dynamicsWorld );
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, fileNames ))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
