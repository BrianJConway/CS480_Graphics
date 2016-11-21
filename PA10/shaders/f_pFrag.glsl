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
           
          in vec3 fN;
          in vec3 fE;
          
          in vec2 texture; 
          in vec3 frag_pos;
          
          out vec4 frag_color; 

          uniform int numLights;
          
          uniform Light lights[MAX_LIGHTS];
          
          uniform mat4 modelMatrix;
          uniform mat4 viewMatrix;          
          uniform float Shininess;

          uniform sampler2D gSampler;
          
          void main(void) 
          {           
            vec4 ambient = vec4( 0.0, 0.0, 0.0, 0.0 );
            vec4 diffuse = vec4( 0.0, 0.0, 0.0, 0.0 );            
            vec4 specular = vec4( 0.0, 0.0, 0.0, 0.0 );
            
            for( int index = 0; index < numLights; index++ )
               {   
                vec3 fL = lights[index].LightPosition.xyz;

                vec3 surfacePos = vec3( modelMatrix * vec4( frag_pos, 1.0 ) );
                vec3 surfaceToLight = normalize( lights[index].LightPosition.xyz - surfacePos );
                float lightToSurfaceAngle = degrees( acos ( dot ( -surfaceToLight, normalize ( lights[index].coneDirection ) ) ) );
                
                if( lights[index].LightPosition.w != 0.0 )
                   {
                    fL -= fE;
                   }                    

                vec3 N = normalize( fN );
                vec3 E = normalize( fE );
                vec3 L = normalize( fL );
                vec3 H = normalize(L + E );
                   
                ambient += lights[index].AmbientProduct;
                
                if( lightToSurfaceAngle < lights[index].coneAngle )
                   {
                    float Kd = max( dot( L, N ), 0.0 );
                    diffuse += Kd * lights[index].DiffuseProduct;
                    
                    if(dot( L, N ) > 0.0 )
                       {                
                        float Ks = pow( max( dot( N, H ), 0.5 ), Shininess );
                        specular += Ks * lights[index].SpecularProduct;
                       }
                   }
                }
                
             frag_color = ambient +  diffuse + specular;
             frag_color *= texture2D( gSampler, texture.xy );
             frag_color.a = 1.0; 
          } 
