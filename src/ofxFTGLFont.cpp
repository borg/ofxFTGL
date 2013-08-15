#include "ofxFTGLFont.h"

ofxFTGLFont::ofxFTGLFont(){
	loaded = false;
	font = NULL;
}


ofxFTGLFont::~ofxFTGLFont(){
	if(font != NULL){
		//delete font;
	}
}


bool ofxFTGLFont::loadFont(string filename, float fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmnt, int dpi){
	fontsize *= 2;
	font = new FTTextureFont(ofToDataPath(filename).c_str());
	
	font->Outset(0.0f, fontsize);
	
	font->CharMap(ft_encoding_unicode);
	
	if(font->Error()){
		ofLogError("ofxFTGLFont") << "Error loading font " << filename;
		delete font;
		return false;
	}
	
	if(!font->FaceSize(fontsize)){
		ofLogError("ofxFTGLFont") << "Failed to set font size";
		delete font;
		return false;
	}
	
	layout.SetFont(font);
	loaded = true;
	return true;
}


float ofxFTGLFont::stringWidth(string c){
	ofRectangle rect = getStringBoundingBox(c, 0, 0);
	return rect.width;
}


float ofxFTGLFont::stringHeight(string c){
	ofRectangle rect = getStringBoundingBox(c, 0, 0);
	return rect.height;
}


bool ofxFTGLFont::isLoaded(){
	return loaded;
}


void ofxFTGLFont::setSize(int size){
	if(loaded){
		font->FaceSize(size);
	}
}


ofRectangle ofxFTGLFont::getStringBoundingBox(string s, float x, float y){
	if(loaded){
		FTBBox bbox = font->BBox(s.c_str());
		return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
	}
	return ofRectangle();
}


ofRectangle ofxFTGLFont::getStringBoundingBox(wstring s, float x, float y){
	if(loaded){
		FTBBox bbox = font->BBox((wchar_t *)s.c_str());
		return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
	}
	return ofRectangle();
}


void ofxFTGLFont::drawParagraph(string paragraph_, float x, float y, float boxWidth, float lineHeight, FTGL::TextAlignment align){
	
	layout.SetLineLength(boxWidth);
	layout.SetAlignment(align);
	layout.SetLineSpacing(lineHeight);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	ofLine(0, 0, boxWidth, 0);
	glScalef(1, -1, 1);
	layout.Render(paragraph_.c_str());
	glPopMatrix();
}


void ofxFTGLFont::drawString(string s, float x, float y){
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1, -1, 1);
	
	font->Render(s.c_str());
	glPopMatrix();
}


void ofxFTGLFont::drawString(wstring s, float x, float y){
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1, -1, 1);
	font->Render((wchar_t *)s.c_str());
	glPopMatrix();
}


