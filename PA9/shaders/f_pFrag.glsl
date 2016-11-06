#version 330
          const int MAX_LIGHTS = 10;
          
          struct Light
             {
              vec4 AmbientProduct;
              vec4 DiffuseProduct;
              vec4 SpecularProduct;
              vec4 LightPosition;
              float coneAngle;
              float coneDirection;
             };
          
          in vec2 texture; 
          in vec3 fN;
          in vec3 fE;
          
          out vec4 frag_color; 
          
          uniform int numLights;
          uniform Light lights[ MAX_LIGHTS ];
          uniform sampler2D gSampler;
          uniform float Shininess;
          
          void main(void) 
          { 
            float attenuation = 1.0;
            vec4 ambient = vec4( 0.0 );
            vec4 diffuse = vec4( 0.0 );
            vec4 specular = vec4( 0.0 );
            
            for( int index = 0; index < numLights; index++ )
               {  
                // Check for directional light
                if( lights[ index ].LightPosition.w == 0.0 )
                   {
                   
                   }               
                 // Otherwise, assume point/spotlight
                 else
                    {
                     // Point light distance affecting attenuation
                     vec3 surfaceToLight = normalize( lights[ index ].LightPosition.xyz );
                     floate distanceToLight = length( L );
                     attenuation = 1.0 / ( 1.0 + light.attenuation * pow( distanceToLight, 2 ) );
                     
                     // Spotlight cone affecting attenuation
                     float lightToSurfaceAngle = degrees( acos ( dot (-surfaceToLight, normalize( light.coneDirection ) ) ) );
                     if( lighttoSurfaceAngle > light.coneAngle )
                        {
                         attenuation = 0.0;
                        }
                    }
                                 
                vec3 fL = lights[ index ].LightPosition.xyz;
             
                 if( LightPosition.w != 0.0 ) 
                    {
     	             fL = lights[ index ].LightPosition.xyz - fE;
     	            }
     	        
                vec3 N = normalize( fN );
                vec3 E = normalize( fE );
                vec3 L = normalize( fL );
                
                vec3 H = normalize( L + E );
                
                ambient += lights[ index ].AmbientProduct;
                
                float Kd = max( dot( L, N ), 0.0 );
                diffuse += Kd * lights[ index ].DiffuseProduct;
                
                float Ks = pow( max( dot( N, H ), 0.0 ), Shininess );
                specular += Ks * lights[ index ].SpecularProduct;
                
                if(dot( L, N ) < 0.0 ) specular += vec4( 0.0, 0.0, 0.0, 1.0 );
               }
             
             frag_color = ( ambient + attenuation * ( diffuse + specular ) ) * texture2D( gSampler, texture.xy );
             frag_color.a = 1.0; 
          } 
          
          
          
