#include "ofxFTGLFont.h"

ofxFTGLFont::ofxFTGLFont(){
	lineHeight = 1.0;
	paragraphWidth = 300;
	textAlignment = FTGL::ALIGN_LEFT;
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

void ofxFTGLFont::setLineHeight(float lh){
	lineHeight = lh;
	if(loaded){
		layout.SetLineSpacing(lh);
	}
}
void ofxFTGLFont::setParagraphWidth(float w){
	paragraphWidth = w;
	if(loaded){
		layout.SetLineLength(w);
	}
}
void ofxFTGLFont::setTextAlignment(FTGL::TextAlignment ta){
	textAlignment = ta;
	if(loaded){
		layout.SetAlignment(ta);
	}
}


ofRectangle ofxFTGLFont::getStringBoundingBox(string s, float x, float y){
	if(loaded){
        
        //compensate for y flip
        float firstLineH=0;
        if(s.size()>0){
            string firstLetter = s.substr(0,1);
            FTBBox bbox = layout.BBox(firstLetter.c_str());
            firstLineH = bbox.Upper().Yf();
        }

        
        
		FTBBox bbox = font->BBox(s.c_str());
		//return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
        
        return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Upper().Yf()-firstLineH, bbox.Upper().Xf(), -bbox.Lower().Yf()+firstLineH);
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

ofRectangle ofxFTGLFont::getParagraphBoundingBox(string s, float x, float y, float boxWidth, float lineHeight_, FTGL::TextAlignment align){
	if(loaded){
		//set temporarly
		if (boxWidth > 0) layout.SetLineLength(boxWidth);
		if (align > 0) layout.SetAlignment(align);
		if (lineHeight_ > 0) layout.SetLineSpacing(lineHeight_);
        
        
        
        //compensate for y flip
        float firstLineH=0;
        if(s.size()>0){
            string firstLetter = s.substr(0,1);
            FTBBox bbox = layout.BBox(firstLetter.c_str());
            firstLineH = bbox.Upper().Yf();
        }
        
		FTBBox bbox = layout.BBox(s.c_str());
        

		//restore
		if (boxWidth > 0) layout.SetLineLength(paragraphWidth);
		if (align > 0) layout.SetAlignment((FTGL::TextAlignment)textAlignment);
		if (lineHeight_ > 0) layout.SetLineSpacing(lineHeight);
        
        //these are flipped around. Natively FTGL sets origin at bottom left of first line.
        //not useful for paragraphs
		return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Upper().Yf()-firstLineH, bbox.Upper().Xf(), -bbox.Lower().Yf()+firstLineH);
	}
	return ofRectangle();
}


float ofxFTGLFont::getTextHeight(string s, float boxWidth, float lineHeight_, FTGL::TextAlignment align){
    if(loaded){
		//set temporarly
		if (boxWidth > 0) layout.SetLineLength(boxWidth);
		if (align > 0) layout.SetAlignment(align);
		if (lineHeight_ > 0) layout.SetLineSpacing(lineHeight_);
        
        
        
        //compensate for y flip
        float firstLineH=0;
        if(s.size()>0){
            string firstLetter = s.substr(0,1);
            FTBBox bbox = layout.BBox(firstLetter.c_str());
            firstLineH = bbox.Upper().Yf();
        }
        
		FTBBox bbox = layout.BBox(s.c_str());
        
        
		//restore
		if (boxWidth > 0) layout.SetLineLength(paragraphWidth);
		if (align > 0) layout.SetAlignment((FTGL::TextAlignment)textAlignment);
		if (lineHeight_ > 0) layout.SetLineSpacing(lineHeight);
        
        //these are flipped around. Natively FTGL sets origin at bottom left of first line.
        //not useful for paragraphs
		return  -bbox.Lower().Yf()+firstLineH;
	}
	return 0;

};

void ofxFTGLFont::drawParagraph(string paragraph_, float x, float y, float boxWidth, float lineHeight_, FTGL::TextAlignment align){
    
	if(loaded){
		//set temporarly
		if (boxWidth > 0) layout.SetLineLength(boxWidth);
		if (align > 0) layout.SetAlignment(align);
		if (lineHeight_ > 0) layout.SetLineSpacing(lineHeight_);
		
        //compensate for y flip
        float firstLineH=0;
        if(paragraph_.size()>0){
            string firstLetter = paragraph_.substr(0,1);        
            FTBBox bbox = layout.BBox(firstLetter.c_str());
            firstLineH = bbox.Upper().Yf();
        }
        
		glPushMatrix();
		glTranslatef(x, y+firstLineH, 0);
		glScalef(1, -1, 1);
		layout.Render(paragraph_.c_str());
		glPopMatrix();
        
		//restore
		if (boxWidth > 0) layout.SetLineLength(paragraphWidth);
		if (align > 0) layout.SetAlignment((FTGL::TextAlignment)textAlignment);
		if (lineHeight_ > 0) layout.SetLineSpacing(lineHeight);
	}
}


void ofxFTGLFont::drawString(string s, float x, float y){
	if(loaded){
        
        
        //compensate for y flip
        float firstLineH=0;
        if(s.size()>0){
            string firstLetter = s.substr(0,1);
            FTBBox bbox = layout.BBox(firstLetter.c_str());
            firstLineH = bbox.Upper().Yf();
        }

        
        
        
		glPushMatrix();
		glTranslatef(x, y+firstLineH, 0);
		glScalef(1, -1, 1);
		
		font->Render(s.c_str());
		glPopMatrix();
	}
}


void ofxFTGLFont::drawString(wstring s, float x, float y){
	if(loaded){
		glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(1, -1, 1);
		font->Render((wchar_t *)s.c_str());
		glPopMatrix();
	}
}


