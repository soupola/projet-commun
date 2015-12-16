#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "../ofElement.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofImage ratio(ofImage i);
		ofImage binerisation(ofImage i);
		ofImage dilatation(ofImage i);
		void erode();
		void dilate();
		void accept();
		void doItAgain();
		void lab(int x, int y);
		bool validate(int x, int y, int dx,int dy);
		void modifyPixel(int x, int y,int color);
		void lab2(int x, int y);
		void righthand();
		void continuer();
		
		ofxCvColorImage ci;

		ofxCvGrayscaleImage test;
		ofxCvGrayscaleImage back;
		ofxCvGrayscaleImage end;


		ofxCvContourFinder cf;
		ofImage img1;
		ofImage img2;

		ofImage img3;

		ofxPanel gui;
		ofxButton plus;
		ofxButton moins;
		ofxButton okb;
		bool affichage;

	
		ofxPanel start;
		ofxButton valide;
		ofxButton cancel;
		bool display;
		int count;

		int level;


		int startX, startY;
		int endX, endY;
		int temp = 0;

		vector<ofElement> bestChemin;
		vector<ofElement> chemin;

		vector<vector <ofElement>> tabElement;
		
		
};
