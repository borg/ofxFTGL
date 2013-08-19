

#pragma once

#include "ofMain.h"
#include "ftgl.h"

class ofxFTGLFont {
	
	enum ofxFTGLFontType {
		
	};
public:
	ofxFTGLFont();
	~ofxFTGLFont();
	//the last parameters don't do anything, but are left in so that ofxFTGLFont
	//can be dropped in in place of ofTrueTypeFont without compiler errors
	bool		loadFont(string filename, float fontsize = 10, bool _bAntiAliased = false, bool _bFullCharacterSet = false, bool makeContours = false, float simplifyAmnt = 0, int dpi = 72);
	bool		isLoaded();
	
	void		setSize(int size);
	void		setLineHeight(float);
	void		setParagraphWidth(float);
	void		setTextAlignment(FTGL::TextAlignment);
    
	ofRectangle getStringBoundingBox(wstring s, float x, float y);
	ofRectangle getStringBoundingBox(string s, float x, float y);
    
	ofRectangle getParagraphBoundingBox(string s, float x, float y, float boxWidth, float lineHeight, FTGL::TextAlignment align);
	ofRectangle getParagraphBoundingBox(wstring s, float x, float y, float boxWidth, float lineHeight, FTGL::TextAlignment align);
	
    
    float getTextHeight(string s, float boxWidth, float lineHeight, FTGL::TextAlignment align);
    
	void		drawString(wstring s, float x, float y);
	void		drawString(string s, float x, float y);
	float		stringHeight(string c);
	float		stringWidth(string c);
	
	FTFont * font;
	FTSimpleLayout layout;
	
	void drawParagraph(string text, float x, float y, float boxWidth = -1.0, float lineHeight = -1.0f, FTGL::TextAlignment align = FTGL::ALIGN_LEFT);
	
protected:
    
	float	lineHeight;
	float	paragraphWidth;
	int		textAlignment; //FTGL::TextAlignment
	bool	loaded;
};

