#include "ofApp.h"
using namespace std;
//--------------------------------------------------------------
void ofApp::setup(){

	affichage = true;
	display = false;
	level = 0;
	count = 1;
	bestChemin.resize(1000000);
	


	gui.setup();
	okb.addListener(this, &ofApp::accept);
	plus.addListener(this, &ofApp::erode);
	moins.addListener(this, &ofApp::dilate);
	gui.add(plus.setup("erosion"));
	gui.add(moins.setup("dilatation"));
	gui.add(okb.setup("ok"));
	
	start.setup();
	valide.addListener(this, &ofApp::continuer);
	cancel.addListener(this, &ofApp::doItAgain);
	start.add(valide.setup("ok"));
	start.add(cancel.setup("cancel"));


	img1.loadImage("lab.jpg");
	img1 = ratio(img1);
	img3 = img1;
	img2.loadImage("back.jpg");
	img2.resize(img1.getWidth(), img1.getHeight());
	back.allocate(img2.getWidth(), img2.getHeight());
	back.setFromPixels(img2.getPixels());

	ci.allocate(img1.getWidth(), img1.getHeight());
	ci.setFromPixels(img1.getPixels());

	img1 = binerisation(img1);
	img2 = img1;

	
	test.allocate(img2.getWidth(), img2.getHeight());
	test.setFromPixels(img2.getPixels());
	end = test;

	
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::accept() {
	affichage = false;
	test.absDiff(back);
	int nbr = cf.findContours(test, 10, test.getWidth()*test.getHeight(), 4, true, true);
	std::cout << "nombre de blobs " << nbr << endl;
	ofRectangle r;
	vector<ofRectangle> vectR;
	for (int i = 0; i < cf.nBlobs; i++)
	{
		r = cf.blobs.at(i).boundingRect;
		vectR.push_back(r);

		std::cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

		std::cout << "Pour blob num " << i << " position x: " << r.getX() << " position y " << r.getY() << endl;
		std::cout << "largeur : " << r.getWidth() << " hauteur " << r.getHeight() << endl;
		std::cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

	}
	ofRectangle tempRect;
	for (int i = 0; i < vectR.size(); i++)
	{
		if (vectR.at(i).getArea() > tempRect.getArea()) {
			tempRect = vectR.at(i);
			vectR.insert(vectR.begin(), vectR.at(i));
		}
	}
	img2.setFromPixels(test.getPixels());
	img2.crop(vectR.at(0).getX(), vectR.at(0).getX(), vectR.at(0).getWidth(), vectR.at(0).getHeight());
	img3.crop(vectR.at(0).getX(), vectR.at(0).getX(), vectR.at(0).getWidth(), vectR.at(0).getHeight());

	img2.resize(100, 200);
	img3.resize(100, 200);

	
	img2.update();
	

	
	tabElement.resize(101);
	for (int i = 0; i < 101; i++) {
		tabElement[i].resize(201);
	}
	
	for (int y = 0; y < img2.getHeight(); y++) {
		for (int x = 0; x < img2.getWidth(); x++) {

			if (img2.getColor(x, y).getBrightness() > 127) {
				//pixel blanc => element mur 
				tabElement[x][y] = ofElement(x, y, img2.getColor(x,y).getBrightness(), false);
			}
			else {
				//tabElement[x][y] = ofElement(x, y, img2.getColor(x, y).getBrightness(), false);
				tabElement[x][y] = ofElement(x, y, img2.getColor(x, y).getBrightness(), false);

			}
		}
	}
	int error = 0;
	for (int y = 0; y < img2.getHeight(); y++) {
		for (int x = 0; x < img2.getWidth(); x++) {
			if (tabElement[x][y].getNbrP() != img2.getColor(x, y).getBrightness()) {
				error++;
			}
		}
	}

	std::cout << "error  "<< error  << endl;
	display = true;
}

void ofApp::continuer() {
	display = false;
	lab(startX, startY);
	
	ofColor red = (255, 0, 0);
	for (int i = 0; i < bestChemin.size(); i++) {
		img3.setColor(bestChemin.at(i).getX(), bestChemin.at(i).getY(), red);
	}
	
	std::cout << " taille du vecteur meilleur chemin " << bestChemin.size()<< endl;

}

void ofApp::erode() {
	level--;
	std::cout << "Niveau " <<level << endl;
	test.dilate();
}
void ofApp::dilate() {
	level++;
	std::cout << "Niveau " << level << endl;
	test.erode();
}

ofImage ofApp::ratio(ofImage i)
{
	ofImage save = i;
	if (i.getHeight() > ofGetWindowHeight() || i.getWidth() > ofGetWindowWidth())
	{
		int hRatio = save.getHeight() / ofGetWindowHeight();
		int wRatio = save.getWidth() / ofGetWindowWidth();
		std::cout << "ratio hauteur : " << hRatio << endl;
		std::cout << "ratio largeur : " << wRatio << endl;

i.resize(save.getHeight() / (hRatio + 1), save.getWidth() / (wRatio + 1));
	}
	i.update();
	return i;
}

ofImage ofApp::binerisation(ofImage i)
{
	i.setImageType(OF_IMAGE_GRAYSCALE);
	for (int y = 0; y < i.getHeight(); y++)
	{
		for (int x = 0; x < i.getWidth(); x++)
		{
			if (i.getColor(x, y).getBrightness()>50)
			{
				i.setColor(x, y, 255);
			}
			else
			{
				i.setColor(x, y, 0);
			}
		}
	}
	i.update();
	return i;
}

ofImage ofApp::dilatation(ofImage i) {
	ofImage imagereturn = i;
	for (int y = 0; y < i.getHeight(); y++)
	{
		for (int x = 0; x < i.getWidth(); x++)
		{
			if (x != 0 && y != 0 && x != i.getWidth() - 1 && y != i.getHeight() - 1)
			{
				if (i.getColor(x, y).getBrightness() < 127)
				{
					imagereturn.setColor(x, y, 0);
					imagereturn.setColor(x - 1, y, 0);
					imagereturn.setColor(x + 1, y, 0);
					imagereturn.setColor(x, y - 1, 0);
					imagereturn.setColor(x, y + 1, 0);
				}
			}
		}
	}
	imagereturn.update();
	return imagereturn;
}

//--------------------------------------------------------------
void ofApp::draw() {
	//img2.draw(0, 0);
	//test.draw(0, 0);
	if (affichage)
	{
		test.draw(0, 0);
		gui.draw();
	}
	else {

		img2.draw(0, 0);
		
		if (display) {
			start.draw();
		}
	}
}

void ofApp::lab2(int x, int y) {

	int dx[8] = { -1,0,1,-1,1,-1,0,1 };
	int dy[8] = { -1,-1,-1,0,0,1,1,1 };
	bool premContact = false;
	while (x != endX && y != endY) {

			if (!premContact) {
			while (!premContact) {
				if (tabElement[x][y + 1].getNbrP() != 255) {
					chemin.push_back(tabElement[x][y]);
				}
				if (tabElement[x][y+1].getNbrP() == 255) {
					premContact = true;
					}
				y++;
				}
			}
			std::cout << "premier contact " <<  endl;

		

	}
}

void ofApp::lab(int x, int y) {
	

	//int dx[8] = { 0,-1,1,-1,1,-1,0,1 };
	//int dy[8] = { -1,-1,-1,0,0,1,1,1 };

	int dx[4] = { 0, 1,-1,0};
	int dy[4] = { -1, 0,0,1};
	



	if (x == endX && y == endY) {
		std::cout << " trouve une sortie " << bestChemin.size() << endl;
		
		if (chemin.size() < bestChemin.size()) {
			bestChemin = chemin;

		}
	}
	else
	{
		for (int i = 0; i < 4; i++) {
			int x1 = x + dx[i];
			int y1 = y + dy[i];
			if (validate(x1, y1, dx[i], dy[i])) {
			chemin.push_back(tabElement[x1][y1]);
			temp = chemin.size();
			std::cout << " size " << chemin.size() << endl;


				tabElement[x1][y1].setUse(true);
				//modifyPixel(x1, y1, 255);
				lab(x1, y1);
				chemin.pop_back();
				tabElement[x1][y1].setUse(false);
				//modifyPixel(x1, y1, 0);

			}
		}
	}
}

void ofApp::righthand() {
	
}

bool ofApp::validate(int x, int y, int dx, int dy) {
	if (!tabElement[x][y].isUsed()) {
		if (0 <= x && x < img2.getWidth()) {
			if (0 <= y && y < img2.getHeight()) {
				if (img2.getColor(x,y).getBrightness()==0 ){
					//if (img2.getColor(x + (5 * dx), y + (5 * dy)).getBrightness() < 127)
						return true;
				}
			}
		}
	}
	return false;
}
void ofApp::modifyPixel(int x, int y,int color) {
	img2.setColor(x, y, color);

	img2.update();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::doItAgain() {
	count = 1;
	ofColor white(255, 255, 255);
	modifyPixel(startX, startY, 255);
	modifyPixel(startX, startY, 255);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (button == 2) {
		if (display) {

			if (x <= img2.getWidth() && y <= img2.getHeight()) {

				if (img2.getColor(x, y).getBrightness() < 127) {

					if (count > 0 && count < 3) {

						if (count == 1) {
							startX = x;
							startY = y;
							std::cout << " start setté  " << endl;
							ofColor red(255, 0, 0);
							modifyPixel(x, y, 255);
							count++;
						}

						else if (count == 2) {
							endX = x;
							endY = y;
							std::cout << " end setté  " << endl;
							ofColor red(255, 0, 0);
							modifyPixel(x, y, 255);
							count++;

						}
					}
					else
					{
						std::cout << " Début et fin déja settés, cliquez sur cancel pour recommencer " << endl;
					}

				}
				else
				{
					std::cout << " Impossible de selectionner un mur" << endl;
				}

			}
			else
			{
				std::cout << " Veuillez cliquer dans l'image" << endl;
			}

		}
	}
	
	std::cout << "x: "<<startX <<" y: " <<startY << endl;
	std::cout << "x: " << endX << " y: " << endY << endl;


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
