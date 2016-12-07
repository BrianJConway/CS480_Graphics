 #version 330

        const int MAX_LIGHTS = 10;
        struct Light
           {
            vec4 AmbientProduct;
            vec4 DiffuseProduct;
            vec4 SpecularProduct;
            vec4 LightPosition;
            float coneAngle;
            vec3 coneDirection;
            float brightness;
           };

          layout (location = 0) in vec3 v_position; 
          layout (location = 1) in vec2 v_texture; 
          layout (location = 2) in vec3 v_normal; 

          out vec3 fN;
          out vec3 fE;
          out vec3 frag_pos;

          out vec2 texture; 
          
          uniform Light lights[MAX_LIGHTS];
          uniform int numLights;
          uniform mat4 projectionMatrix; 
          uniform mat4 viewMatrix;
          uniform mat4 modelMatrix;
          uniform vec4 LightPosition;
 
          void main(void) 
          { 
            frag_pos = v_position;
            vec4 v = vec4( v_position, 1.0 );
            fN = v_normal;
            fE = v_position;

            texture = v_texture;
             
            gl_Position = projectionMatrix * viewMatrix * modelMatrix * v;     
          } 
