#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    font.loadFont("ScalaSansOffcPro-Bold.ttf", 12);
    
    
    lorem = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    
    singleLine = "Keys: l,r,c,j set alignment";
    
    
    alignment = FTGL::ALIGN_JUSTIFY;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    int margin = 20;
    int w = 1000*ofGetMouseX()/ofGetWidth();
    float lh = 1;
    
    ofSetBackgroundColor(0,0,0);
    font.setParagraphWidth(w);
    font.setTextAlignment(alignment);
    
    ofRectangle rect = font.getParagraphBoundingBox(lorem, margin,margin, w, lh, alignment);

    
    
    
    ofFill();
    ofSetColor(100,0,100);
    ofRect(rect.x,rect.y,rect.width,rect.height);
    
    ofSetColor(255,255,255);
    
    
    font.setLineHeight(lh);
    font.drawParagraph(lorem, margin,margin);
    
    
    
    rect = font.getStringBoundingBox(singleLine, rect.x + rect.width+margin,rect.y);
    
    ofFill();
    ofSetColor(100,0,100);
    ofRect(rect.x,rect.y,rect.width,rect.height);
    
    ofSetColor(255,255,255);
    font.drawString(singleLine, rect.x,rect.y);
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
    if(key=='j'){
         alignment = FTGL::ALIGN_JUSTIFY;
    }
    
    if(key=='c'){
        alignment = FTGL::ALIGN_CENTER;
    }
    if(key=='r'){
        alignment = FTGL::ALIGN_RIGHT;
    }
    if(key=='l'){
        alignment = FTGL::ALIGN_LEFT;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
