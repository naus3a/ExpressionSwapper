//
//  Jaw.cpp
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

#include "Jaw.h"

Jaw::Jaw(){
    int totV = 14;
    msh.setMode(OF_PRIMITIVE_TRIANGLES);
    for(int i=0;i<totV;i++){
        msh.addVertex(ofVec2f(0,0));
        msh.addColor(ofColor::white);
    }
    makeTriangles();
    makeTexture();
    
    vtxCor.push_back(4);
    vtxCor.push_back(5);
    vtxCor.push_back(6);
    vtxCor.push_back(7);
    vtxCor.push_back(8);
    vtxCor.push_back(9);
    vtxCor.push_back(10);
    vtxCor.push_back(11);
    vtxCor.push_back(12);
    vtxCor.push_back(35);
    vtxCor.push_back(34);
    vtxCor.push_back(33);
    vtxCor.push_back(32);
    vtxCor.push_back(31);
}

void Jaw::makeTriangles(){
    msh.addTriangle(0, 13, 1);
    msh.addTriangle(13, 1, 12);
    msh.addTriangle(12, 1, 2);
    msh.addTriangle(2, 12, 3);
    msh.addTriangle(3, 12, 11);
    msh.addTriangle(11, 3, 4);
    msh.addTriangle(4, 11, 5);
    msh.addTriangle(5, 11, 10);
    msh.addTriangle(10, 5, 6);
    msh.addTriangle(6, 10, 7);
    msh.addTriangle(7, 10, 9);
    msh.addTriangle(9, 7, 8);
}

void Jaw::makeTexture(){
    ofImage img;
    bool b = img.loadImage("snap.png");
    fboTxt.allocate(512, 512, GL_RGB);
    fboTxt.begin();
    ofClear(0, 0, 0);
    if(b){
        img.draw(0, 0, fboTxt.getWidth(), fboTxt.getHeight());
    }
    fboTxt.end();
    
    float ww = fboTxt.getWidth()/8;
    for(int i=0;i<9;i++){
        msh.addTexCoord(ofVec2f(i*ww,fboTxt.getHeight()));
    }
    ww = fboTxt.getWidth()/4;
    for(int i=9;i<14;i++){
        ofVec2f tt(0,0);
        tt.x = fboTxt.getWidth()-((i-9)*ww);
        msh.addTexCoord(tt);
    }
}

void Jaw::setFromTracked(ofMesh *tMsh){
    for(int i=0;i<msh.getNumVertices();i++){
        msh.setVertex(i, tMsh->getVertex(vtxCor[i]));
    }
}

void Jaw::colorFromPixels(ofPixels pix){
    for(int i=0;i<msh.getNumVertices();i++){
        ofVec2f vv = msh.getVertex(i);
        ofColor cc = pix.getColor(vv.x, vv.y);
        msh.setColor(i, cc);
    }
}

void Jaw::draw(){
    ofPushStyle();
    msh.drawWireframe();
    ofPopStyle();
}

void Jaw::snapshot(ofPixels pix){
    
    ofImage img;
    img.setFromPixels(pix);
    
    vector<ofVec3f> oV;
    vector<ofVec2f> oT;
    vector<ofIndexType> oI;
    
    for(int i=0;i<msh.getNumVertices();i++){
        oV.push_back(msh.getTexCoord(i));
        oT.push_back(msh.getVertex(i));
    }
    
    for(int i=0;i<msh.getNumIndices();i++){
        oI.push_back(msh.getIndex(i));
    }
    
    ofMesh oMsh;
    oMsh.setMode(OF_PRIMITIVE_TRIANGLES);
    oMsh.addVertices(oV);
    oMsh.addTexCoords(oT);
    oMsh.addIndices(oI);
    
    fboTxt.begin();
    ofClear(0, 255);
    img.getTextureReference().bind();
    oMsh.draw();
    img.getTextureReference().unbind();
    fboTxt.end();
    
    ofPixels oPix;
    fboTxt.readToPixels(oPix);
    ofImage oImg;
    oImg.setFromPixels(oPix);
    oImg.saveImage("snap.png");
}