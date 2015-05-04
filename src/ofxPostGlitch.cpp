//
//  ofxPostGlitch.cpp
//
//  Created by maxilla inc. on 2013/02/01.
//  Updated by TatsuyaOGth. on 2014/10~
//

#include "ofxPostGlitch.h"

static const string VERTEX_SHADER_NAME  = "ofxPostGlitch.vert";
static const string MODULE_NAME         = "ofxPostGlitch";

bool ofxPostGlitch::setup(ofFbo *buffer_, const string & shaderDirectory)
{
    setFbo(buffer_);
    return setShaders(shaderDirectory);
}

bool ofxPostGlitch::setup(ofFbo *buffer_)
{
    return setup(buffer_, OFXPOSTGLITCH_DEFAULT_SHADER_DIR);
}

void ofxPostGlitch::setFbo(ofFbo *buffer_)
{
	targetBuffer = buffer_;
	buffer_size.set(buffer_->getWidth(), buffer_->getHeight());
	ShadingBuffer.allocate(buffer_size.x,buffer_size.y);
}

bool ofxPostGlitch::reloadShaders(const string & shaderDirectory)
{
    int num = dir.size();
    if (shaderDirectory != "")
    {
        num = dir.listDir(shaderDirectory);
    }
    for (int i = 0; i < num; i++)
    {
        if (!addShader(dir.getPath(i)))
        {
            return false;
        }
    }
}

bool ofxPostGlitch::setShaders(const string &shaderDirectory)
{
    reset();
    int num = dir.listDir(shaderDirectory);
    for (int i = 0; i < num; i++)
    {
        if (!addShader(dir.getPath(i)))
        {
            return false;
        }
    }
    return true;
}

bool ofxPostGlitch::addShader(const string &shaderPath)
{
    string fileName = ofSplitString(shaderPath, "/").back();
    if (fileName == VERTEX_SHADER_NAME) return true;
    vector<string> shaderName = ofSplitString(fileName, ".");
    if (shaderName.size() != 2)
    {
        ofLogError(MODULE_NAME) << "inviled shader name: " << fileName;
        return false;
    }
    if (shaderName[1] == "frag" || shaderName[1] == "fr")
    {
        shaders.push_back(SHADER());
        shaders.back().flug = false;
        shaders.back().shaderName = shaderName[0];
        shaders.back().level = 1.0;
        if (!shaders.back().shader.load(dir.path() + "/" + VERTEX_SHADER_NAME, shaderPath))
        {
            ofLogError(MODULE_NAME) << "faild load shader: " << shaderPath;
            shaders.pop_back();
            return false;
        }
        ofLogVerbose(MODULE_NAME) << "load shader: " << shaderPath;
    }
    return true;
}

void ofxPostGlitch::setFx(const string & shaderName, bool enabled)
{
    SHADER * s = getShaderFromName(shaderName);
    if (s != NULL) s->flug = enabled;
}

void ofxPostGlitch::setFx(int shaderIndex, bool enabled)
{
    if (shaderIndex < 0 || shaderIndex >= shaders.size()) return;
    shaders[shaderIndex].flug = enabled;
}

void ofxPostGlitch::toggleFx(const string & shaderName)
{
    SHADER * s = getShaderFromName(shaderName);
    if (s != NULL) s->flug ^= true;
}

void ofxPostGlitch::toggleFx(int shaderIndex)
{
    if (shaderIndex < 0 || shaderIndex >= shaders.size()) return;
    shaders[shaderIndex].flug ^= true;
}

void ofxPostGlitch::setFxTo(const string & shaderName, float second)
{
    this->setFx(shaderName, true);
    timers.insert(make_pair(shaderName, second));
}

void ofxPostGlitch::setFxTo(int shaderIndex, float second)
{
    this->setFx(shaderIndex, true);
    timers.insert(make_pair(shaders[shaderIndex].shaderName, second));
}

void ofxPostGlitch::setFxLevel(const string &shaderName, float level)
{
    SHADER * s = getShaderFromName(shaderName);
    if (s != NULL) s->level = level;
}

void ofxPostGlitch::setFxLevel(int shaderIndex, float level)
{
    if (shaderIndex < 0 || shaderIndex >= shaders.size()) return -1;
    shaders[shaderIndex].level = level;
}

float ofxPostGlitch::getFxLevel(const string &shaderName)
{
    SHADER * s = getShaderFromName(shaderName);
    return s->level;
}

float ofxPostGlitch::getFxLevel(int shaderIndex)
{
    if (shaderIndex < 0 || shaderIndex >= shaders.size()) return -1;
    return shaders[shaderIndex].level;
}

void ofxPostGlitch::setAllFxLevel(float level)
{
    for (int i = 0;i < shaders.size(); i++)
    {
        shaders[i].level = level;
    }
}

bool ofxPostGlitch::getFx(const string & shaderName)
{
    SHADER * s = getShaderFromName(shaderName);
    if (s != NULL) return s->flug;
    return false;
}

void ofxPostGlitch::generateFx()
{
	if (targetBuffer == NULL){
		ofLog(OF_LOG_WARNING, "ofxPostGlitch --- Fbo is not allocated.");
		return;
	}

	static int step = ofRandom(4,15);
	float v[2];
	v[0] = ofRandom(3);v[1] = ofRandom(3);
	if (ofGetFrameNum() % step == 0){
		step = ofRandom(10,30);
		ShadeVal[0] = ofRandom(100);
        ShadeVal[1] = ofRandom(100);
		ShadeVal[2] = ofRandom(100);
		ShadeVal[3] = ofRandom(100);
	}

    ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);
	glClearColor(0, 0, 0, 0.0);

	for (int i = 0;i < shaders.size(); i++)
    {
		if (shaders[i].flug)
        {
			shaders[i].shader.begin();
			shaders[i].shader.setUniformTexture	("image"		,*targetBuffer,0);
			shaders[i].shader.setUniform1i		("trueWidth"	,buffer_size.x);
			shaders[i].shader.setUniform1i		("trueHeight"	,buffer_size.y);
			shaders[i].shader.setUniform1f		("rand"			,ofRandom(1));
			shaders[i].shader.setUniform1f		("mouseX"		,ofGetMouseX());
			shaders[i].shader.setUniform1f		("mouseY"		,ofGetMouseY());
			shaders[i].shader.setUniform1f		("val1"			,ShadeVal[0]);
			shaders[i].shader.setUniform1f		("val2"			,ShadeVal[1]);
			shaders[i].shader.setUniform1f		("val3"			,ShadeVal[2]);
			shaders[i].shader.setUniform1f		("val4"			,ShadeVal[3]);
			shaders[i].shader.setUniform1f		("timer"		,ofGetElapsedTimef());
			shaders[i].shader.setUniform2fv		("blur_vec"		,v);
            shaders[i].shader.setUniform1f      ("level"        ,shaders[i].level);

			ShadingBuffer.begin();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ofVec3f rectPoints[4];
            rectPoints[0].set(0, 0, 0);
            rectPoints[1].set(buffer_size.x, 0, 0);
            rectPoints[2].set(buffer_size.x, buffer_size.y, 0);
            rectPoints[3].set(0, buffer_size.y, 0);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, sizeof(ofVec3f), &rectPoints[0].x);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            
			ShadingBuffer.end();
			shaders[i].shader.end();

			targetBuffer->begin();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ShadingBuffer.draw(0, 0,buffer_size.x,buffer_size.y);
			targetBuffer->end();
		}
	}
    ofPopStyle();
}

void ofxPostGlitch::listShaders()
{
    vector<SHADER>::iterator it = shaders.begin();
    int i = 0;
    while (it != shaders.end())
    {
        cout << "index: " << i << "  | shader name: " << it->shaderName << endl;
        ++it;
        ++i;
    }
}

ofxPostGlitch::SHADER * ofxPostGlitch::getShaderFromName(const string & name)
{
    vector<SHADER>::iterator it = shaders.begin();
    while (it != shaders.end())
    {
        if (it->shaderName == name)
        {
            return &(*it);
        } else ++it;
    }
    return NULL;
}

void ofxPostGlitch::reset()
{
    shaders.clear();
    timers.clear();
}

void ofxPostGlitch::onUpdate(ofEventArgs &data)
{
    if (!timers.empty())
    {
        float lastFrameTime = ofGetLastFrameTime();
        map<string, float>::iterator it = timers.begin();
        while (it != timers.end())
        {
            it->second -= lastFrameTime;
            if (it->second < 0)
            {
                this->setFx(it->first, false);
                timers.erase(it++);
            } else ++it;
        }
    }
}
