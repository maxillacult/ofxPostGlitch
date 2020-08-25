//
//  PGShaderConstants.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/26/15.
//
//

#ifndef ofxPostGlitchExample_PGShaderConstants_h
#define ofxPostGlitchExample_PGShaderConstants_h

#include "ofMain.h"

#define GLSL120(shader) "#version 120 \n" #shader
#define GLSL150(shader) "#version 150 \n" #shader

static const string gl120VertShader = GLSL120(
                                              varying vec3 pos;
                                              
                                              void main(void)
                                              {
                                                  pos = gl_Vertex.xyz;
                                                  gl_Position = ftransform();
                                              }
                                              );

static const string gl150VertShader = GLSL150(
                                              uniform mat4 projectionMatrix;
                                              uniform mat4 modelViewMatrix;
                                              uniform mat4 textureMatrix;
                                              uniform mat4 modelViewProjectionMatrix;
                                              
                                              in vec4  position;
                                              in vec2  texcoord;
                                              in vec4  color;
                                              in vec3  normal;
                                              
                                              out vec3 pos;
                                              
                                              void main()
                                              {
                                                  pos = position.xyz;
                                                  gl_Position = modelViewProjectionMatrix * position;
                                              }
                                              );

#endif
