#version 330
          
          in vec3 fN;
          in vec3 fE;
          in vec3 fL;
          
          in vec2 texture; 
          in vec3 frag_pos;
          
          out vec4 frag_color; 

          uniform vec4 AmbientProduct;
          uniform vec4 DiffuseProduct;
          uniform vec4 SpecularProduct;
          uniform mat4 modelMatrix;
          uniform mat4 viewMatrix;          
          uniform vec4 LightPosition;
          uniform float Shininess;
          uniform vec3 coneDirection;
          uniform float coneAngle;

          uniform sampler2D gSampler;
          
          void main(void) 
          {           
            float attenuation = 1.0;      
            vec3 surfacePos = vec3( modelMatrix * vec4( frag_pos, 1.0 ) );
            vec3 surfaceToLight = normalize( LightPosition.xyz - surfacePos );
            float lightToSurfaceAngle = degrees( acos ( dot ( -surfaceToLight, normalize ( coneDirection ) ) ) );
            
            if( lightToSurfaceAngle > coneAngle )
               {
                attenuation = 0.0;
               }
            
            vec3 N = normalize( fN );
            vec3 E = normalize( fE );
            vec3 L = normalize( fL );
            vec3 H = normalize(L + E );
                
            vec4 ambient = AmbientProduct;
                
            float Kd = max( dot( L, N ), 0.0 );
            vec4 diffuse = Kd * DiffuseProduct;
                
            float Ks = pow( max( dot( N, H ), 0.5 ), Shininess );
            vec4 specular = Ks * SpecularProduct;
                
            if(dot( L, N ) < 0.0 )
               {
                specular = vec4( 0.0, 0.0, 0.0, 1.0 );
               }
             
             frag_color = ambient + attenuation * ( diffuse + specular );
             frag_color *= texture2D( gSampler, texture.xy );
             frag_color.a = 1.0; 
          } 
          
          
          
