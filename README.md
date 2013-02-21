# ofxPostGlitch
This add-on applies a glitch effect to the FBO using openFrameworks.  
We recommend using openFrameworks v0073 or later.

## Usage :
You need at least two classes 'ofFbo' and 'ofxPostGlitch' to use it.

	ofFbo myFbo;
	ofxPostGlitch myGlitch;

In the Setup(), you should give FBO's pointer to ofxPostGlitch instance.
Then allocate the FBO.

    void testApp::setup(){
    	myFbo.allocate(640,480);
    	myGlitch.setup(&myFbo);
    }

Choose wether to apply effect or not with the setFX function.
After that use generateFX function and apply all enabled effects.

	void testApp::update(){
		myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE,true);
	}

	void testApp::draw(){
		myGlitch.generateFx();
		myFbo.draw(0,0);
	}

More details can be found in the example project file.

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