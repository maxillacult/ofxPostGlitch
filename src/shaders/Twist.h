//
//  Twist.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/27/15.
//
//

#ifndef ofxPostGlitchExample_Twist_h
#define ofxPostGlitchExample_Twist_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Twist : public ofShader
{
public:
    
    Twist() : ofShader()
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
                                     uniform int trueWidth;
                                     uniform int trueHeight;
                                     uniform float rand;
                                     uniform int flags;
                                     uniform vec2 blur_vec;
                                     uniform float val1;
                                     uniform float val2;
                                     uniform float val3;
                                     uniform float val4;
                                     uniform float timer;
                                     uniform float mouseX;
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     void main (void)
                                     {
                                         pix_w = 1.0 / float(imgWidth);
                                         pix_h = 1.0 / float(imgHeight);
                                         
                                         vec2 texCoord = vec2(max(3.0,min(float(trueWidth)  ,pos.x+sin(pos.y/(153.25*rand*rand)*rand+rand*val2+timer*3.0)*val3)),
                                                              max(3.0,min(float(trueHeight),pos.y+cos(pos.x/(251.57*rand*rand)*rand+rand*val2+timer*2.4)*val3)-3.));
                                         
                                         
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
                                     uniform int trueWidth;
                                     uniform int trueHeight;
                                     uniform float rand;
                                     uniform int flags;
                                     uniform vec2 blur_vec;
                                     uniform float val1;
                                     uniform float val2;
                                     uniform float val3;
                                     uniform float val4;
                                     uniform float timer;
                                     uniform float mouseX;
                                     int flgs;
                                     float pix_w;
                                     float pix_h;
                                     varying vec3 pos;
                                     
                                     void main (void)
                                     {
                                         pix_w = 1.0 / float(imgWidth);
                                         pix_h = 1.0 / float(imgHeight);
                                         
                                         vec2 texCoord = vec2(max(3.0,min(float(trueWidth)  ,pos.x+sin(pos.y/(153.25*rand*rand)*rand+rand*val2+timer*3.0)*val3)),
                                                              max(3.0,min(float(trueHeight),pos.y+cos(pos.x/(251.57*rand*rand)*rand+rand*val2+timer*2.4)*val3)-3.));
                                         
                                         
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
    
    ~Twist() { unload(); }
};

#endif
