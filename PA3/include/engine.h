#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>
#include <cstdlib>
#include <vector>
using namespace std;

#include "window.h"
#include "graphics.h"

class Engine
{
  public:
    Engine(string name, int width, int height);
    Engine(string name);
    ~Engine();
    bool Initialize( std::string shaders[] );
    void Run();
    void Keyboard();
    void Mouse();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
  
  private:
    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
    
    
    // Holds movement settings for objects
    // First element controls rotation pausing and unpausing
    // Second element controls orbit pausing and unpausing
    // Third element controls rotation direction
    // Fourth element controls orbit direction
    vector<string> motionSettings;
};

#endif // ENGINE_H
