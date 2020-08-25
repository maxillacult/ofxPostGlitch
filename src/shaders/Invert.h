//
//  Invert.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/26/15.
//
//

#ifndef ofxPostGlitchExample_Invert_h
#define ofxPostGlitchExample_Invert_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Invert : public ofShader
{
public:
    
    Invert() : ofShader()
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
                                     uniform float val1;
                                     uniform float val2;
                                     uniform float val3;
                                     uniform float val4;
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     void main (void)
                                     {
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         vec4 col = texture(image,texCoord);;
                                         col.r = 1.0 - col.r;
                                         col.g = 1.0 - col.g;
                                         col.b = 1.0 - col.b;
                                         fragColor = col;
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
                                     uniform float val1;
                                     uniform float val2;
                                     uniform float val3;
                                     uniform float val4;
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     varying vec3 pos;
                                     
                                     void main (void)
                                     {
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         vec4 col = texture2DRect(image,texCoord);;
                                         col.r = 1.0 - col.r;
                                         col.g = 1.0 - col.g;
                                         col.b = 1.0 - col.b;
                                         gl_FragColor = col;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Invert() { unload(); }
};

#endif
