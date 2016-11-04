#include <cstdlib>
#include <string>
#include <algorithm>
#include "engine.h"

using namespace std;

/*
Function returns whether or not input is formatted correctly. Only returns true 
if both vertex and fragment shaders are specified in the correct format.

Stores vertex shader filename in inputData[ 1 ]
Stores fragment shader filename in inputData[ 2 ]
*/
bool validateInput( int numArgs, char **inputStrings, string inputData[] );

bool checkEndsWith( const string& testString, const string& endStr );

int main(int argc, char **argv)
{
    // Initialize program/variables
    string inputInfo[ 3 ];
  
    // Check if shaders and object were specified correctly
    if( validateInput( argc, argv, inputInfo ) )
    {
        // Start an engine and run it then cleanup after
        Engine *engine = new Engine("Tutorial Window Name", 1600, 900);
        if(!engine->Initialize( inputInfo ))
        {
          printf("The engine failed to start.\n");
          delete engine;
          engine = NULL;
   
        }
      
        engine->Run();
        delete engine;
        engine = NULL;
    }
    
    return 0;  
}

bool validateInput( int numArgs, char **inputStrings, string inputData[] )
{
    // Initialize function/variables
    vector<string> inputArgs;
    vector<string>::iterator tempIterator;
    string temp;
    int index;
    bool noArgs, noVertex, noVName, noFragment, noFName, result;
    
        // Get vector of strings from inputs
        for( index = 0; index < numArgs; index++ )
        {
            temp = inputStrings[ index ];
            inputArgs.push_back( temp );
        }

    
    // Check if help requested
    if( ( numArgs == 2 ) && ( inputArgs[ 1 ] == "--h" ) )
    {
        cout << "USAGE: './Tutorial -v (VERTEX SHADER FILE) -f (FRAGMENT SHADER FILE)'"
             << endl 
             << "Shader files must be of type '.glsl'"
             << endl;
             
        return false;
    }
    
    // Detect possible errors in program input
        
        // Check for incorrect number of arguments
        noArgs = ( numArgs < 3 );
        
        // Check if vertex shader specified
        tempIterator = find( inputArgs.begin(), inputArgs.end(), "-v" );
        noVertex = tempIterator == inputArgs.end();     
        
        // Check if vertex shader specified but bad or missing filename 
        // Returns false if '-v' at end of input or missing .glsl extension 
        noVName = !(noVertex) &&                    
                  ( next( tempIterator ) == inputArgs.end() || 
                    !checkEndsWith( *( next( tempIterator ) ), ".glsl" ) ); 

        // Check if fragment shader specified
        tempIterator = find( inputArgs.begin(), inputArgs.end(), "-f" );
        noFragment = tempIterator == inputArgs.end();     
        
        // Check if fragment shader specified but bad or missing filename 
        // Returns false if '-v' at end of input or missing .glsl extension 
        noFName = !(noFragment) &&                    
                  ( next( tempIterator ) == inputArgs.end() || 
                    !checkEndsWith( *( next( tempIterator ) ), ".glsl" ) ); 
                        
            
    // Check if incorrect input detected 
    if( noArgs || noVertex || noVName || noFragment || noFName )                         
    {
        // Check if too few or too many arguments
        if( noArgs )
        {
            cout << "ERROR: No arguments specified."
                 << endl;   
        }
        // Check if '-v' not specified
        if( !noArgs && noVertex )
        {
            cout << "ERROR: Vertex shader not specified."
                 << endl;        
        }
        // Check if vertex shader filename not specified
        else if( noVName )
        {
           cout << "ERROR: Vertex shader filename missing or incorrect extension"
                 << endl;  
        }
                // Check if '-f' not specified
        if( !noArgs && noFragment )
        {
            cout << "ERROR: Fragment shader not specified."
                 << endl;        
        }
        // Otherwise check if fragment shader filename not specified
        else if( noFName )
        {
           cout << "ERROR: Fragment shader filename missing or incorrect extension"
                << endl;  
        }
        
        cout << "Try './Tutorial --h' for more information" 
             << endl;
             
        result = false;
    }
    // Otherwise, assume all input formatted correctly
    else
    {
        // Load vertex shader filename into first element of output array
        tempIterator = find( inputArgs.begin(), inputArgs.end(), "-v" );
        inputData[ 0 ] = *( next(tempIterator ) );
        
        // Load fragment shader filename into second element of output array
        tempIterator = find( inputArgs.begin(), inputArgs.end(), "-f" );
        inputData[ 1 ] = *( next(tempIterator ) );
        
        result = true;
    }
    
 return result;
}

bool checkEndsWith( const string& testString, const string& endStr )
{
    // Initialize function/variables
    int sizeDiff = testString.length() - endStr.length();
    
    // Check if ending string can be contained in test string
    if( testString.size() >= endStr.length() )
    {
        // Compare end of test string to ending string
        return ( testString.compare( sizeDiff, endStr.length(), endStr ) == 0 );
    }
    else
    {
        return false;
    }
}




