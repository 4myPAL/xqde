//
// C++ Interface: xqdeanimation
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEANIMATION_H
#define XQDEANIMATION_H

class XQDEIcon;


class XQDEAnimation{
public:
    XQDEAnimation(int type=0, XQDEIcon *icon=0,int endEffect=0, class XQDEAction *test=0,class XQDEAction *endAction=0);//,int ar=1);

    QStringList getAnimationTypes();

	void step();
	void stepAgain();
	int currentStep;
	int endEffect;
	int autoRemove;
	class XQDEAction *endAction;
	XQDEIcon *icon;
	inline int getType(){return type;}

    ~XQDEAnimation();
protected:
	void resetCurrentStep();
	int type;
	int maxCicle;
	class XQDEAction *test;

};

#endif
