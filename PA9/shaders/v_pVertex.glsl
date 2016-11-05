 #version 330
 
          struct Light
             {
              vec4 AmbientProduct;
              vec4 DiffuseProduct;
              vec4 SpecularProduct;
              vec4 LightPosition;
             };
          
          layout (location = 0) in vec4 v_position; 
          layout (locaiton = 1) in vec3 v_normal; 
          layout (locaiton = 2) in vec2 v_texture; 
          
          out vec4 color; 
          out vec2 texture;
          
          uniform int numLights;          
          uniform Light lights[ numLights ];
          uniform mat4 projectionMatrix; 
          uniform mat4 ModelView; 
          uniform float Shininess;
          
          void main(void) 
          { 
            vec3 pos = ( ModelView * v_position ).xyz
            
            vec4 ambient = vec4( 0.0 );
            vec4 diffuse = vec4( 0.0 );
            vec4 specular = vec4( 0.0 );
            
            for( int index = 0; index < numLights; index++ )
               {               
                vec3 L = normalize( lights[ index ].LightPosition.xyz - pos );
                vec3 E = normalize( -pos );
                vec3 H = normalize( L + E );
                
                vec3 N = normalize( ModelView * vec4( v_normal, 0.0 ) ).xyz;
                
                ambient += lights[ index ].AmbientProduct;
                
                float Kd = max( dot( L, N ), 0.0 );
                diffuse += Kd * lights[ index ].DiffuseProduct;
                
                float Ks = pow( max( dot( N, H ), 0.0 ), Shininess );
                specular += Ks * lights[ index ].SpecularProduct;
                
                if(dot( L, N ) < 0.0 ) specular += vec4( 0.0, 0.0, 0.0, 1.0 );
                
                gl_Position = Projection * ModelView * vPosition;     
               }

            
            color = ambient + diffuse + specular;
            color.a = 1.0;
            
            texture = v_texture;
          } 
          
          
          
