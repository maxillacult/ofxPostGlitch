# ofxPostGlitch
This addon applies glitch effects to FBO with openframeworks.
we recommend to use openFrameworks after v0073.

## Usage :
You need at least two classes 'ofFbo' and 'ofxPostGlitch' to use it.

	ofFbo myFbo;
	ofxPostGlitch myGlitch;

In Setup(), you should give FBO's pointer to ofxPostGlitch instance.  
Then the FBO must be allocated.

    void testApp::setup(){
    	myFbo.allocate(640,480);
    	myGlitch.setup(&myFbo);
    }

Decide to apply effect or not with setFX function.  
After that, call generateFX function and apply all enabled effects.

	void testApp::update(){
		myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE,true);
	}

	void testApp::draw(){
		myGlitch.generateFx();
		myFbo.draw(0,0);
	}

You can check more detail in example project.

## Glitch FXs	
- Convergence
- Glow
- Shaker
- Cutslider
- Twist
- Outline
- Noise
- Slitscan
- Swell
- Invert

## Color remap FXs
- Highcontrast
- Blueraise
- Redraise
- Greenraise
- Blueinvert
- Redinvert
- Greeninvert

## Developer info
maxilla inc.
[http://maxilla.jp](http://maxilla.jp)

maxilla cult
[http://cult.maxilla.jp](http://cult.maxilla.jp)