 #version 330
          
          layout (location = 0) in vec3 v_position; 
          layout (location = 1) in vec2 v_texture; 
          layout (location = 2) in vec3 v_normal; 
          
          out vec4 color; 
          out vec2 texture;
          
          uniform vec4 AmbientProduct;
          uniform vec4 DiffuseProduct;
          uniform vec4 SpecularProduct;
          uniform vec4 LightPosition;
          uniform vec3 coneDirection;
          uniform float coneAngle;
          
          uniform mat4 projectionMatrix; 
          uniform mat4 viewMatrix;
          uniform mat4 modelMatrix; 
          uniform float Shininess;
          
          void main(void) 
          { 
            float attenuation = 1.0;
            vec4 v = vec4( v_position, 1.0 );
            vec3 pos = ( viewMatrix * modelMatrix * v ).xyz;
            
            vec3 surfaceToLight = normalize( LightPosition.xyz - v_position );
            float lightToSurfaceAngle = degrees( acos ( dot ( -surfaceToLight, normalize ( coneDirection ) ) ) );
            
            if( lightToSurfaceAngle > coneAngle )
               {
                attenuation = 0.0;
               }
            
            vec3 L = normalize( LightPosition.xyz - pos );
            vec3 E = normalize( -pos );
            vec3 H = normalize( L + E );

            vec3 N = normalize( viewMatrix * modelMatrix * vec4( v_normal, 0.0 ) ).xyz;
                
            vec4 ambient = AmbientProduct;
                
            float Kd = max( dot( L, N ), 0.0 );
            vec4 diffuse = Kd * DiffuseProduct;
            float Ks = pow( max( dot( N, H ), 0.0 ), Shininess );
            vec4 specular = Ks * SpecularProduct;
                
            if(dot( L, N ) < 0.0 )
               {
                specular = vec4( 0.0, 0.0, 0.0, 1.0 );
               }
                   
            gl_Position = projectionMatrix * viewMatrix * modelMatrix * v;     
            
            color = ambient + attenuation * ( diffuse + specular );
            color.a = 1.0;
            
            texture = v_texture;
          } 
          
          
          
