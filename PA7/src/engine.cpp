
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

  // Start the graphics
  m_graphics = new Graphics();
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
      Mouse();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

// Handles mouse click events
void Engine::Mouse()
   {
    // Initialize function/variables
    Camera* m_camera = m_graphics->getCamera();
    
    // Checks for mouse button event
    if(m_event.type == SDL_MOUSEMOTION )
       {
        m_camera->processMouseMovement( m_event.motion.xrel, m_event.motion.yrel );
       }
   }

void Engine::Keyboard()
   {
    // Initialize function/varaibles 
    Camera* m_camera = m_graphics->getCamera();
    
    if(m_event.type == SDL_QUIT)
       {
        m_running = false;
       }
    else if (m_event.type == SDL_KEYDOWN)
       {
        if (m_event.key.keysym.sym == SDLK_ESCAPE)
           {
            m_running = false;
           }
        // Toggle rotation direction key
        else if(m_event.key.keysym.sym == SDLK_w)
           {
            m_camera->processKeyboard( "FORWARD" );
           }
        // Toggle rotation on/off key
        else if(m_event.key.keysym.sym == SDLK_s)
           {
            m_camera->processKeyboard( "BACK" );
           }
        // Toggle moon orbit direction key
        else if(m_event.key.keysym.sym == SDLK_a)
           {
            m_camera->processKeyboard( "LEFT" );
           }
        // Toggle moon rotationrere on/off 
        else if(m_event.key.keysym.sym == SDLK_d)
           {
            m_camera->processKeyboard( "RIGHT" );
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
