//testApp.cpp
//
// Copyright Enrico <naus3a> Viola 2015
// This file is part of ExpressionSwapper.
//
//ExpressionSwapper is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//ExpressionSwapper is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with ExpressionSwapper.  If not, see <http://www.gnu.org/licenses/>.

#include "testApp.h"

using namespace ofxCv;

bool bSwap;
bool bGrid;

void testApp::setup() {
#ifdef TARGET_OSX
	//ofSetDataPathRoot("../data/");
#endif
	ofSetVerticalSync(true);
	cloneReady = false;
	cam.initGrabber(1280, 720);
	clone.setup(cam.getWidth(), cam.getHeight());
	ofFbo::Settings settings;
	settings.width = cam.getWidth();
	settings.height = cam.getHeight();
	maskFbo.allocate(settings);
	srcFbo.allocate(settings);
    fboCam.allocate(settings);
	camTracker.setup();
	
    bSwap=true;
    bGrid=true;
    bDebug=false;
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		camTracker.update(toCv(cam));
		
		cloneReady = camTracker.getFound();
		if(cloneReady) {
			camMesh = camTracker.getImageMesh();
			
            jaw.setFromTracked(&camMesh);
            //jaw.colorFromPixels(cam.getPixelsRef());
            
			maskFbo.begin();
			ofClear(0, 255);
			//camMesh.draw();
            jaw.msh.draw();
			maskFbo.end();
			
			srcFbo.begin();
			ofClear(0, 255);
			//src.bind();
			//camMesh.draw();
			//src.unbind();
            jaw.fboTxt.getTextureReference().bind();
            jaw.msh.draw();
            jaw.fboTxt.getTextureReference().unbind();
            srcFbo.end();
			
            fboCam.begin();
            ofClear(0, 255);
            cam.draw(0, 0);
            //jaw.fboTxt.getTextureReference().bind();
            //jaw.msh.draw();
            //jaw.fboTxt.getTextureReference().unbind();
            fboCam.end();
            
			clone.setStrength(16);
			clone.update(srcFbo.getTextureReference(), fboCam.getTextureReference(), maskFbo.getTextureReference());
		}
	}
}

void testApp::draw() {
	ofSetColor(255);
	
    if(bSwap){
        if( cloneReady) {
            clone.draw(0, 0);
        } else {
            cam.draw(0, 0);
        }
    }else{
        cam.draw(0,0);
    }
	
    //if(bGrid){
        //camTracker.draw();
    //}
    
	if(camTracker.getFound()) {
	    ofPushStyle();
        ofSetColor(ofColor::green);
        ofRect(0, ofGetHeight()-20, 20, 20);
        if(bGrid){
            jaw.draw();
        }
        ofPopStyle();
        if(bDebug)
            cam.draw(0, 0, cam.getWidth()/4, cam.getHeight()/4);
        
	}
	
}


void testApp::keyPressed(int key){
	switch(key){
        case 's':
            bSwap=!bSwap;
            break;
        case 'g':
            bGrid=!bGrid;
            break;
        case ' ':
            jaw.snapshot(cam.getPixelsRef());
            break;
        case 'd':
            bDebug=!bDebug;
            break;
	}
	
}
