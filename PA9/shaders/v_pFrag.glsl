 #version 330
 
          layout (location = 0) in vec4 v_position; 
          layout (location = 1) in vec2 v_texture; 
          layout (location = 2) in vec3 v_normal; 
          
          out vec3 fN;
          out vec3 fE;
          out vec2 texture; 
          
          uniform mat4 projectionMatrix; 
          uniform mat4 ModelView; 
 
          void main(void) 
          { 
            fN = v_normal;
            fE = v_position.xyz;
            
            gl_Position = Projection * ModelView * v_position;     
            texture = v_texture; 
          } 
          
          
          
