//
//  Noise.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/27/15.
//
//

#ifndef ofxPostGlitchExample_Noise_h
#define ofxPostGlitchExample_Noise_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Noise : public ofShader
{
public:
    
    Noise() : ofShader()
    {
        string vertexShader;
        string fragmentShader;
        
        if (ofIsGLProgrammableRenderer())
        {
            vertexShader = gl150VertShader;
            
            fragmentShader = GLSL150(
                                     uniform sampler2DRect image;
                                     uniform float rand;
                                     uniform int range;
                                     
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     //
                                     // Description : Array and textureless GLSL 2D simplex noise function.
                                     //      Author : Ian McEwan, Ashima Arts.
                                     //  Maintainer : ijm
                                     //     Lastmod : 20110822 (ijm)
                                     //     License : Copyright (C) 2011 Ashima Arts. All rights reserved.
                                     //               Distributed under the MIT License. See LICENSE file.
                                     //               https://github.com/ashima/webgl-noise
                                     //
                                     
                                     vec3 mod289(vec3 x)
                                     {
                                         return x - floor(x * (1.0 / 289.0)) * 289.0;
                                     }
                                     
                                     vec2 mod289(vec2 x)
                                     {
                                         return x - floor(x * (1.0 / 289.0)) * 289.0;
                                     }
                                     
                                     vec3 permute(vec3 x)
                                     {
                                         return mod289(((x*34.0)+1.0)*x);
                                     }
                                     
                                     float snoise(vec2 v)
                                     {
                                         const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
                                                             0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
                                                             -0.577350269189626,  // -1.0 + 2.0 * C.x
                                                             0.024390243902439); // 1.0 / 41.0
                                         // First corner
                                         vec2 i  = floor(v + dot(v, C.yy) );
                                         vec2 x0 = v -   i + dot(i, C.xx);
                                         
                                         // Other corners
                                         vec2 i1;
                                         //i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
                                         //i1.y = 1.0 - i1.x;
                                         i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
                                         // x0 = x0 - 0.0 + 0.0 * C.xx ;
                                         // x1 = x0 - i1 + 1.0 * C.xx ;
                                         // x2 = x0 - 1.0 + 2.0 * C.xx ;
                                         vec4 x12 = x0.xyxy + C.xxzz;
                                         x12.xy -= i1;
                                         
                                         // Permutations
                                         i = mod289(i); // Avoid truncation effects in permutation
                                         vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
                                                          + i.x + vec3(0.0, i1.x, 1.0 ));
                                         
                                         vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
                                         m = m*m ;
                                         m = m*m ;
                                         
                                         // Gradients: 41 points uniformly over a line, mapped onto a diamond.
                                         // The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)
                                         
                                         vec3 x = 2.0 * fract(p * C.www) - 1.0;
                                         vec3 h = abs(x) - 0.5;
                                         vec3 ox = floor(x + 0.5);
                                         vec3 a0 = x - ox;
                                         
                                         // Normalise gradients implicitly by scaling m
                                         // Approximation of: m *= inversesqrt( a0*a0 + h*h );
                                         m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
                                         
                                         // Compute final noise value at P
                                         vec3 g;
                                         g.x  = a0.x  * x0.x  + h.x  * x0.y;
                                         g.yz = a0.yz * x12.xz + h.yz * x12.yw;
                                         return 130.0 * dot(m, g);
                                     }
                                     
                                     void main (void)
                                     {
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         vec4 col = texture(image,texCoord);
                                         
                                         col.rgb = col.rgb + snoise(vec2(pos.x*pos.y+rand*231.5 , pos.x+pos.y-rand*324.1))*0.5;
                                         
                                         fragColor = col.rgba;
                                     }
                                     );
        }
        else
        {
            vertexShader = gl120VertShader;
            
            fragmentShader = GLSL120(
                                     uniform sampler2DRect image;
                                     uniform float rand;
                                     uniform int range;
                                     
                                     varying vec3 pos;
                                     
                                     //
                                     // Description : Array and textureless GLSL 2D simplex noise function.
                                     //      Author : Ian McEwan, Ashima Arts.
                                     //  Maintainer : ijm
                                     //     Lastmod : 20110822 (ijm)
                                     //     License : Copyright (C) 2011 Ashima Arts. All rights reserved.
                                     //               Distributed under the MIT License. See LICENSE file.
                                     //               https://github.com/ashima/webgl-noise
                                     //
                                     
                                     vec3 mod289(vec3 x)
                                     {
                                         return x - floor(x * (1.0 / 289.0)) * 289.0;
                                     }
                                     
                                     vec2 mod289(vec2 x)
                                     {
                                         return x - floor(x * (1.0 / 289.0)) * 289.0;
                                     }
                                     
                                     vec3 permute(vec3 x)
                                     {
                                         return mod289(((x*34.0)+1.0)*x);
                                     }
                                     
                                     float snoise(vec2 v)
                                     {
                                         const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
                                                             0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
                                                             -0.577350269189626,  // -1.0 + 2.0 * C.x
                                                             0.024390243902439); // 1.0 / 41.0
                                         // First corner
                                         vec2 i  = floor(v + dot(v, C.yy) );
                                         vec2 x0 = v -   i + dot(i, C.xx);
                                         
                                         // Other corners
                                         vec2 i1;
                                         //i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
                                         //i1.y = 1.0 - i1.x;
                                         i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
                                         // x0 = x0 - 0.0 + 0.0 * C.xx ;
                                         // x1 = x0 - i1 + 1.0 * C.xx ;
                                         // x2 = x0 - 1.0 + 2.0 * C.xx ;
                                         vec4 x12 = x0.xyxy + C.xxzz;
                                         x12.xy -= i1;
                                         
                                         // Permutations
                                         i = mod289(i); // Avoid truncation effects in permutation
                                         vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
                                                          + i.x + vec3(0.0, i1.x, 1.0 ));
                                         
                                         vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
                                         m = m*m ;
                                         m = m*m ;
                                         
                                         // Gradients: 41 points uniformly over a line, mapped onto a diamond.
                                         // The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)
                                         
                                         vec3 x = 2.0 * fract(p * C.www) - 1.0;
                                         vec3 h = abs(x) - 0.5;
                                         vec3 ox = floor(x + 0.5);
                                         vec3 a0 = x - ox;
                                         
                                         // Normalise gradients implicitly by scaling m
                                         // Approximation of: m *= inversesqrt( a0*a0 + h*h );
                                         m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
                                         
                                         // Compute final noise value at P
                                         vec3 g;
                                         g.x  = a0.x  * x0.x  + h.x  * x0.y;
                                         g.yz = a0.yz * x12.xz + h.yz * x12.yw;
                                         return 130.0 * dot(m, g);
                                     }
                                     
                                     void main (void)
                                     {
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         vec4 col = texture2DRect(image,texCoord);
                                         
                                         col.rgb = col.rgb + snoise(vec2(pos.x*pos.y+rand*231.5 , pos.x+pos.y-rand*324.1))*0.5;
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Noise() { unload(); }
};

#endif
