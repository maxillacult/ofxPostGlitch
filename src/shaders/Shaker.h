//
//  Shaker.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/27/15.
//
//

#ifndef ofxPostGlitchExample_Shaker_h
#define ofxPostGlitchExample_Shaker_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Shaker : public ofShader
{
public:
    
    Shaker() : ofShader()
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
                                         
                                         
                                         vec4 col_s[5];
                                         vec4 col_s2[5];
                                         for (int i = 0;i < 5;i++){
                                             col_s[i] = texture(image,texCoord +  vec2(-pix_w*float(i)*blur_vec.x ,-pix_h*float(i)*blur_vec.y));
                                             col_s2[i] = texture(image,texCoord + vec2( pix_w*float(i)*blur_vec.x , pix_h*float(i)*blur_vec.y));
                                         }
                                         col_s[0] = (col_s[0] + col_s[1] + col_s[2] + col_s[3] + col_s[4])/5.0;
                                         col_s2[0]= (col_s2[0]+ col_s2[1]+ col_s2[2]+ col_s2[3]+ col_s2[4])/5.0;
                                         col = (col_s[0] + col_s2[0]) / 2.0;
                                         
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
                                         
                                         
                                         vec4 col_s[5];
                                         vec4 col_s2[5];
                                         for (int i = 0;i < 5;i++){
                                             col_s[i] = texture2DRect(image,texCoord +  vec2(-pix_w*float(i)*blur_vec.x ,-pix_h*float(i)*blur_vec.y));
                                             col_s2[i] = texture2DRect(image,texCoord + vec2( pix_w*float(i)*blur_vec.x , pix_h*float(i)*blur_vec.y));
                                         }
                                         col_s[0] = (col_s[0] + col_s[1] + col_s[2] + col_s[3] + col_s[4])/5.0;
                                         col_s2[0]= (col_s2[0]+ col_s2[1]+ col_s2[2]+ col_s2[3]+ col_s2[4])/5.0;
                                         col = (col_s[0] + col_s2[0]) / 2.0;
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Shaker() { unload(); }
};

#endif
