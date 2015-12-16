#include "ofElement.h"



ofElement::ofElement(int posY, int posX,  int passage,bool state)
{
	X = posX;
	Y = posY;
	nbrP = passage;
	used = state;
}
ofElement::ofElement()
{

}

int ofElement::getX() {
	return X;
}

int ofElement::getY() {
	return Y;
}

int ofElement::getNbrP() {
	return nbrP;
}

bool ofElement::isUsed() {
	return used;
}


void ofElement::setX(int x) {
	X = x;
}

void ofElement::setY(int y) {
	Y = y;
}

void ofElement::setNbrp(int nbp) {
	nbrP = nbp;
}

void ofElement::setUse(bool state)
{
	used = state;
}

ofElement::~ofElement()
{
}
