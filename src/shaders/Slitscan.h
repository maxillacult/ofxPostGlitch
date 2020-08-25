//
//  Slitscan.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/27/15.
//
//

#ifndef ofxPostGlitchExample_Slitscan_h
#define ofxPostGlitchExample_Slitscan_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Slitscan : public ofShader
{
public:
    
    Slitscan() : ofShader()
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
                                         pix_w = 1.0 / float(imgWidth);
                                         pix_h = 1.0 / float(imgHeight);
                                         flgs = flags;
                                         
                                         float slit_h = val3;
                                         
                                         vec2 texCoord = vec2(3.0+floor(pos.x/slit_h)*slit_h ,pos.y);
                                         vec4 col = texture(image,texCoord);
                                         
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
                                         pix_w = 1.0 / float(imgWidth);
                                         pix_h = 1.0 / float(imgHeight);
                                         flgs = flags;
                                         
                                         float slit_h = val3;
                                         
                                         vec2 texCoord = vec2(3.0+floor(pos.x/slit_h)*slit_h ,pos.y);
                                         vec4 col = texture2DRect(image,texCoord);
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Slitscan() { unload(); }
};

#endif
