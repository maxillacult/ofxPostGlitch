# ofxPostGlitch
このアドオンは、openFrameworks上でグリッチエフェクトを適用するためのアドオンです。

## Usage :
このアドオンを実現させるためには、最低2つのクラスを必要とします。
ofFboと、ofxPostGlitchです。

    ofFbo myFbo;
    ofxPostGlitch myGlitch;

Setup関数内で、FboのポインタをofxPostGlitchクラスに渡します。
この時、Fboはallocateでサイズが決まっている必要があります。

    void testApp::setup(){
    	myFbo.allocate(640,480);
    	myGlitch.setup(&myFbo);
    }

setFx関数でエフェクトの種類とON/OFFを指定します。
その後generateFx関数を呼び出して、Fboにエフェクトを適用させてください。

	void testApp::update(){
		myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE,true);
	}

	void testApp::draw(){
		myGlitch.generateFx();
		myFbo.draw(0,0);
	}

更に細かな情報に関しては、サンプルを参照してください。

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
[maxilla inc.](http://maxilla.jp)

[maxilla cult](http://cult.maxilla.jp)