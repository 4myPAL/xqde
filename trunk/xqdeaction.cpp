//
// C++ Implementation: xqdeaction
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QProcess>
#include <QTimer>

#include "xqdebasket.h"
#include "xqdeaction.h"
#include "xqdeanimation.h"

void XQDE_IconAddedNewAnimation();


XQDEAction::XQDEAction()
{
	ActionType="";
	isEnabled=1;
	Action="";
	ActionCounter=0;
	Pointer=0;
	disableActionForWhile=new QTimer();
	connect(disableActionForWhile, SIGNAL(timeout()), SLOT(enableActionAgain()));
}

XQDEAction::~XQDEAction()
{
    if (disableActionForWhile) delete disableActionForWhile;
}


void XQDEAction::enableActionAgain()
{
	isEnabled=1;
}

void XQDEAction::doit()
{
	qWarning("void XQDEAction::doit()");
	if(ActionType=="exec" && isEnabled>0)
	{
		qWarning("XQDEAction::doit() Starting:%s",Action.toAscii().data());
		QProcess::startDetached(Action);
		ActionCounter++;
		isEnabled=0;
                disableActionForWhile->start(2000);
                //start fly animation
		if(Pointer)
		{
			XQDEIcon *newIcon=(XQDEIcon *)Pointer;
			if(newIcon->animations->count()<1)
			{
				XQDEAction *RequiredAction=new XQDEAction();
				RequiredAction->ActionType="isnotrunning";
				XQDEAction *EndAction=NULL;
				RequiredAction->Pointer=Pointer;
				XQDEAnimation *RequiredAnimation=new XQDEAnimation(4,newIcon,0,RequiredAction,EndAction);
                                newIcon->animations->append(RequiredAnimation);
                                newIcon->animationsNextFrameCounter=1;
                                XQDE_IconAddedNewAnimation();
			}
		}

	}
	if(ActionType=="removeicon")
	{
                qWarning("XQDEAction::doit() removeicon:%ld (%d)",(long)Pointer,Basket->items.size());
		ActionCounter++;
		/*
		for(int i=0;i<Basket->items.size();i++)
		{
			XQDEIcon *delItem=Basket->items.at(i);
			if(delItem==Pointer)
			{
				Basket->items.takeAt(i);
				i--;
				Basket->sgeBasket_As_Changed(6, NULL, NULL);
				qWarning("I'm going to delete: %ld (%d)",(long)delItem,Basket->items.size());
				//  TODO: CACATA ASSURDA
				//delItem->animations->clear();
				//delItem->animationsNextFrameCounter=0;
				//delete delItem;
				
				break;
			}
		}
		*/
	}
	qWarning("void XQDEAction::doit() end");
}


int XQDEAction::doTest()
{
	if(ActionType=="isrunning")
	{
		for(int i=0;i<Basket->items.size();i++)
		{
			XQDEIcon *testItem=Basket->items.at(i);
			if(testItem==Pointer)
			{
				return testItem->isRunning();
			}
		}
	}
	if(ActionType=="isnotrunning")
	{
		for(int i=0;i<Basket->items.size();i++)
		{
			XQDEIcon *testItem=Basket->items.at(i);
			if(testItem==Pointer)
			{
				if(testItem->isRunning()>0)return 0;
				else return 1;
			}
		}
	}
	return 0;
}
