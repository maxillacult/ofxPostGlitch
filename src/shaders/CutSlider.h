//
//  CutSlider.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/26/15.
//
//

#ifndef ofxPostGlitchExample_CutSlider_h
#define ofxPostGlitchExample_CutSlider_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class CutSlider : public ofShader
{
public:
    
    CutSlider() : ofShader()
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
                                         
                                         vec2 texCoord = vec2(pos.x, pos.y);
                                         vec4 col = texture(image,texCoord);
                                         vec4 col_s = texture(image,texCoord + vec2(floor(sin(pos.y/30.0*rand+rand*rand))*30.0*rand,0));
                                         
                                         col = col_s;
                                         
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
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     varying vec3 pos;
                                     
                                     void main (void)
                                     {
                                         pix_w = 1.0;
                                         pix_h = 1.0;
                                         flgs = flags;
                                         
                                         vec2 texCoord = vec2(pos.x, pos.y);
                                         vec4 col = texture2DRect(image,texCoord);
                                         vec4 col_s = texture2DRect(image,texCoord + vec2(floor(sin(pos.y/30.0*rand+rand*rand))*30.0*rand,0));
                                         
                                         col = col_s;
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~CutSlider() { unload(); }
};

#endif
