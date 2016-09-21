
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
  
/*
  // Set default values for object motion
  motionSettings[ 0 ] = "START";
  motionSettings[ 1 ] = "START";
  motionSettings[ 2 ] = "NORMAL";
  motionSettings[ 3 ] = "NORMAL";
*/

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

bool Engine::Initialize( std::string shaders[] )
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
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, shaders ))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // Set default values for planet motion settings  
  // First element controls rotation pausing and unpausing
  // Second element controls orbit pausing and unpausing
  // Third element controls rotation direction
  // Fourth element controls orbit direction
  motionSettings.push_back("START");
  motionSettings.push_back("START");
  motionSettings.push_back("NORMAL");
  motionSettings.push_back("NORMAL");

  // Set default values for moon motion settings  
  // Fifth element controls rotation pausing and unpausing
  // Sixth element controls orbit pausing and unpausing
  // Seventh element controls rotation direction
  // Eighth element controls orbit direction
  motionSettings.push_back("START");
  motionSettings.push_back("START");
  motionSettings.push_back("NORMAL");
  motionSettings.push_back("NORMAL");
  
  // No errors
  return true;
}

void Engine::Run()
{
  // initialize function/variables
  
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
    m_graphics->Update(m_DT, motionSettings);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

// Handles mouse click events
void Engine::Mouse()
   {
    // Checks for mouse button event
    if(m_event.type == SDL_MOUSEBUTTONDOWN )
       {
        // Left mouse button toggles orbit direction
        if( m_event.button.button == SDL_BUTTON_LEFT )
           {
            // Check if orbit is normal direction
            if( motionSettings[ 3 ] == "NORMAL" )
               {
                // reverse orbit
                motionSettings[ 3 ] = "REVERSE";
               }
            // Otherwise, assume orbit is reversed   
            else
               {
                // reverse orbit
                motionSettings[ 3 ] = "NORMAL";
               }
           }
        // Right mouse button toggles orbit on/off
        else if( m_event.button.button == SDL_BUTTON_RIGHT )
           {
            // Check if rotation is enabled
            if( motionSettings[ 1 ] == "START" )
               {
                // Disable rotation
                motionSettings[ 1 ] = "PAUSE";
               }
            // Otherwise, assume rotation is disabled   
            else
               {
                // Enable rotation
                motionSettings[ 1 ] = "START";
               }
           }
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
        if (m_event.key.keysym.sym == SDLK_ESCAPE)
           {
            m_running = false;
           }
        // Toggle rotation direction key
        else if(m_event.key.keysym.sym == SDLK_q)
           {
            // Check if rotation is normal
            if( motionSettings[ 2 ] == "NORMAL" )
               {
                // reverse rotation
                motionSettings[ 2 ] = "REVERSE";
               }
            // Otherwise, assume rotation is reversed   
            else
               {
                // set normal rotation
                motionSettings[ 2 ] = "NORMAL";
               }
           }
        // Toggle rotation on/off key
        else if(m_event.key.keysym.sym == SDLK_w)
           {
            // Check if rotation is enabled
            if( motionSettings[ 0 ] == "START" )
               {
                // Disable rotation
                motionSettings[ 0 ] = "PAUSE";
               }
            // Otherwise, assume rotation is disabled   
            else
               {
                // Enable rotation
                motionSettings[ 0 ] = "START";
               }
           }
        // Toggle all movement key
        else if(m_event.key.keysym.sym == SDLK_p)
           {
            // Check if either rotation or orbit is enabled
            if( motionSettings[ 0 ] == "START" || 
                motionSettings[ 1 ] == "START" ||
                motionSettings[ 4 ] == "START" ||               
                motionSettings[ 5 ] == "START"  )
               {
                // Disable rotation and orbit
                motionSettings[ 0 ] = "PAUSE";
                motionSettings[ 1 ] = "PAUSE";
                motionSettings[ 4 ] = "PAUSE";
                motionSettings[ 5 ] = "PAUSE";
               }
            // Otherwise, assume both rotation and orbit is disabled   
            else
               {
                // Enable rotation and orbit
                motionSettings[ 0 ] = "START";
                motionSettings[ 1 ] = "START";
                motionSettings[ 4 ] = "START";
                motionSettings[ 5 ] = "START";
               }
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
