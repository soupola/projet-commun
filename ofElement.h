#pragma once
#include "ofMain.h"
class ofElement
{
public:
	ofElement(int posY, int posX, int passage, bool state);
	ofElement::ofElement();
	~ofElement();
	int getX();
	int getY();
	int getNbrP();
	bool isUsed();

	void setX(int x);
	void setY(int y);
	void setNbrp(int nbrp);
	void setUse(bool state);

private: 
	int X;
	int Y;
	bool used;
	int	nbrP;

};

