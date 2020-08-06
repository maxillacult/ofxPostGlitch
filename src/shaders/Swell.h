//
//  Swell.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/27/15.
//
//

#ifndef ofxPostGlitchExample_Swell_h
#define ofxPostGlitchExample_Swell_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Swell : public ofShader
{
public:
    
    Swell() : ofShader()
    {
        string vertexShader;
        string fragmentShader;
        
        if (ofIsGLProgrammableRenderer())
        {
            vertexShader = gl150VertShader;
            
            fragmentShader = GLSL150(
                                     uniform sampler2DRect image;
                                     uniform int imgWidth;
                                     uniform int imgHeight;
                                     uniform float rand;
                                     uniform int flags;
                                     uniform vec2 blur_vec;
                                     uniform float timer;
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     void main (void)
                                     {
                                         pix_w = 1.0;
                                         pix_h = 1.0;
                                         flgs = flags;
                                         
                                         vec2 texCoord = vec2(pos.x,pos.y);
                                         vec4 col = texture(image,texCoord);
                                         vec4 col_s = texture(image,texCoord + vec2(sin(pos.y*0.03+timer*20.0)*(6.0+12.0*rand),0));
                                         
                                         col = col_s;
                                         //    col.r = col.r * sin(rand);
                                         //	col.g = col.g * sin(rand*1.34+pos.y);
                                         //	col.b = col.b * cos(rand*1.56+pos.x*pos.y);
                                         
                                         fragColor = col.rgba;
                                     }
                                     );
        }
        else
        {
            vertexShader = gl120VertShader;
            
            fragmentShader = GLSL120(
                                     uniform sampler2DRect image;
                                     uniform int imgWidth;
                                     uniform int imgHeight;
                                     uniform float rand;
                                     uniform int flags;
                                     uniform vec2 blur_vec;
                                     uniform float timer;
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     varying vec3 pos;
                                     
                                     void main (void)
                                     {
                                         pix_w = 1.0;
                                         pix_h = 1.0;
                                         flgs = flags;
                                         
                                         vec2 texCoord = vec2(pos.x,pos.y);
                                         vec4 col = texture2DRect(image,texCoord);
                                         vec4 col_s = texture2DRect(image,texCoord + vec2(sin(pos.y*0.03+timer*20.0)*(6.0+12.0*rand),0));
                                         
                                         col = col_s;
                                         //    col.r = col.r * sin(rand);
                                         //	col.g = col.g * sin(rand*1.34+pos.y);
                                         //	col.b = col.b * cos(rand*1.56+pos.x*pos.y);
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Swell() { unload(); }
};

#endif
