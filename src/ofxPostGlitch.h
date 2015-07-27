//
//  ofxPostGlitch.h
//
//  Created by maxilla inc. on 2013/02/01.
//
//

#ifndef __ofxPostGlitchExample__ofxPostGlitch__
#define __ofxPostGlitchExample__ofxPostGlitch__

#include "ofMain.h"

#include "Convergence.h"
#include "CutSlider.h"
#include "Glow.h"
#include "Invert.h"
#include "Noise.h"
#include "Outline.h"
#include "Shaker.h"
#include "Slitscan.h"
#include "Swell.h"
#include "Twist.h"
#include "CrBlueinvert.h"
#include "CrBlueraise.h"
#include "CrGreeninvert.h"
#include "CrGreenraise.h"
#include "CrHighContrast.h"
#include "CrRedinvert.h"
#include "CrRedraise.h"

#define GLITCH_NUM 17

enum ofxPostGlitchType{
	OFXPOSTGLITCH_CONVERGENCE,
	OFXPOSTGLITCH_GLOW,
	OFXPOSTGLITCH_SHAKER,
	OFXPOSTGLITCH_CUTSLIDER,
	OFXPOSTGLITCH_TWIST,
	OFXPOSTGLITCH_OUTLINE,
	OFXPOSTGLITCH_NOISE,
	OFXPOSTGLITCH_SLITSCAN,
	OFXPOSTGLITCH_SWELL,
	OFXPOSTGLITCH_INVERT,
	OFXPOSTGLITCH_CR_HIGHCONTRAST,
	OFXPOSTGLITCH_CR_BLUERAISE,
	OFXPOSTGLITCH_CR_REDRAISE,
	OFXPOSTGLITCH_CR_GREENRAISE,
	OFXPOSTGLITCH_CR_REDINVERT,
	OFXPOSTGLITCH_CR_BLUEINVERT,
	OFXPOSTGLITCH_CR_GREENINVERT
};

class ofxPostGlitch{
public:

	ofxPostGlitch(){
		targetBuffer = NULL;
        
        Convergence convergence;
        Glow glow;
        Shaker shaker;
        CutSlider cutSlider;
        Twist twist;
        Outline outline;
        Noise noise;
        Slitscan slitscan;
        Swell swell;
        Invert invert;
        CrHighContrast crHighContrast;
        CrBlueraise crBlueraise;
        CrRedraise crRedraise;
        CrGreenraise crGreenraise;
        CrRedinvert crRedinvert;        
        CrBlueinvert crBlueinvert;
        CrGreeninvert crGreeninvert;
        
		shader[0] = convergence;
        shader[1] = glow;
		shader[2] = shaker;
		shader[3] = cutSlider;
        shader[4] = twist;
		shader[5] = outline;
		shader[6] = noise;
		shader[7] = slitscan;
		shader[8] = swell;
		shader[9] = invert;
        shader[10] = crHighContrast;
		shader[11] = crBlueraise;
		shader[12] = crRedraise;
		shader[13] = crGreenraise;
		shader[14] = crRedinvert;
		shader[15] = crBlueinvert;
		shader[16] = crGreeninvert;
	}

	/* Initialize & set target Fbo */
	void setup(ofFbo* buffer_);

	/* Set target Fbo */
	void setFbo(ofFbo* buffer_);

	/* Switch each effects on/off */
	void setFx(ofxPostGlitchType type_,bool enabled);

	/* Toggle each effects on/off */
	void toggleFx(ofxPostGlitchType type_);

	/* Return current effect's enabled info*/
	bool getFx(ofxPostGlitchType type_);

	/* Apply enable effects to target Fbo */
	void generateFx();

protected:
	bool		bShading[GLITCH_NUM];
	ofShader	shader[GLITCH_NUM];
	ofFbo*		targetBuffer;
	ofFbo		ShadingBuffer;
	ofPoint		buffer_size;
	float ShadeVal[4];
};

#endif /* defined(__ofxPostGlitchExample__ofxPostGlitch__) */
