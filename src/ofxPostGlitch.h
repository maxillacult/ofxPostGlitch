//
//  ofxPostGlitch.h
//
//  Created by maxilla inc. on 2013/02/01.
//  Updated by TatsuyaOGth. on 2014/10~
//

#ifndef __ofxPostGlitchExample__ofxPostGlitch__
#define __ofxPostGlitchExample__ofxPostGlitch__

#include "ofMain.h"

static const int    GLITCH_NUM  = 17;

static const string OFXPOSTGLITCH_DEFAULT_SHADER_DIR    = "Shaders";
static const string OFXPOSTGLITCH_CONVERGENCE           = "convergence";
static const string OFXPOSTGLITCH_GLOW                  = "glow";
static const string OFXPOSTGLITCH_SHAKER                = "shaker";
static const string OFXPOSTGLITCH_CUTSLIDER             = "cut_slider";
static const string OFXPOSTGLITCH_TWIST                 = "twist";
static const string OFXPOSTGLITCH_OUTLINE               = "outline";
static const string OFXPOSTGLITCH_NOISE                 = "noise";
static const string OFXPOSTGLITCH_SLITSCAN              = "slitscan";
static const string OFXPOSTGLITCH_SWELL                 = "swell";
static const string OFXPOSTGLITCH_INVERT                = "invert";
static const string OFXPOSTGLITCH_CR_HIGHCONTRAST       = "crHighContrast";
static const string OFXPOSTGLITCH_CR_BLUERAISE          = "crBlueraise";
static const string OFXPOSTGLITCH_CR_REDRAISE           = "crRedraise";
static const string OFXPOSTGLITCH_CR_GREENRAISE         = "crGreenraise";
static const string OFXPOSTGLITCH_CR_REDINVERT          = "crRedinvert";
static const string OFXPOSTGLITCH_CR_BLUEINVERT         = "crBlueinvert";
static const string OFXPOSTGLITCH_CR_GREENINVERT        = "crGreeninvert";

class ofxPostGlitch
{
protected:
    typedef struct _SHADER
    {
        bool        flug;
        string      shaderName;
        ofShader    shader;
        float       level; ///< Level is multipurpose value
    } SHADER;
    
    vector<SHADER>      shaders;
    map<string, float>  timers;
    ofDirectory dir;
    ofFbo*      targetBuffer;
    ofFbo		ShadingBuffer;
    ofPoint		buffer_size;
    float ShadeVal[4];
    
    SHADER * getShaderFromName(const string & name);
    void reset();
    void onUpdate(ofEventArgs &data);
    
public:

	ofxPostGlitch()
    {
		targetBuffer = NULL;
        ofAddListener(ofEvents().update, this, &ofxPostGlitch::onUpdate);
	}

	/* Initialize, set target Fbo and set shaders from directory */
	bool setup(ofFbo* buffer_, const string & shaderDirectory);
    bool setup(ofFbo* buffer_);

	/* Set target Fbo */
	void setFbo(ofFbo* buffer_);
    
    /* Set shaders from directory */
    bool setShaders(const string & shaderDirectory);
    
    /* Add a shader */
    bool addShader(const string & shaderPath);

	/* Switch each effects on/off */
	void setFx(const string & shaderName,bool enabled);
    void setFx(int shaderIndex, bool enabled);

	/* Toggle each effects on/off */
	void toggleFx(const string & shaderName);
    void toggleFx(int shaderIndex);
    
    /* Enable each effects for <t>sec. */
    void setFxTo(const string & shaderName, float second);
    void setFxTo(int shaderIndex, float second);

	/* Return current effect's enabled info*/
	bool getFx(const string & shaderName);

	/* Apply enable effects to target Fbo */
	void generateFx();
    
    void listShaders();
    
    /* Set level */
    void setFxLevel(const string & shaderName, float level);
    void setFxLevel(int shaderIndex, float level);
    void setAllFxLevel(float level);
    float getFxLevel(const string & shaderName);
    float getFxLevel(int shaderIndex);
};

#endif /* defined(__ofxPostGlitchExample__ofxPostGlitch__) */
