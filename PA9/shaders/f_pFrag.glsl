#version 330

          struct Light
             {
              vec4 AmbientProduct;
              vec4 DiffuseProduct;
              vec4 SpecularProduct;
              vec4 LightPosition;
             };
          
          in vec2 texture; 
          in vec3 fN;
          in vec3 fE;
          
          out vec4 frag_color; 
          
          uniform int numLights;
          uniform Light lights[ numLights ];
          uniform sampler2D gSampler;
          uniform float Shininess;
          
          void main(void) 
          { 
            vec4 ambient = vec4( 0.0 );
            vec4 diffuse = vec4( 0.0 );
            vec4 specular = vec4( 0.0 );
            
            for( int index = 0; index < numLights; index++ )
               {               
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
             
             frag_color = ( ambient + diffuse + specular ) * texture2D( gSampler, texture.xy );
             frag_color.a = 1.0; 
          } 
          
          
          
