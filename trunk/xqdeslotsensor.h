//
// C++ Interface: xqdeslotsensor
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDESLOTSENSOR_H
#define XQDESLOTSENSOR_H

#include <QString>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
	class XQDESlotSensor
	{
		public:
		virtual inline ~XQDESlotSensor()
		{
		}
		inline XQDESlotSensor()
		{
			Counter=0;
			Sensor="";
			Type="";
			Slot="";
		}
		virtual class QDomElement &writeXMLElement(class QDomElement &);
		virtual class QDomElement &readXMLElement(class QDomElement &);
		unsigned long Counter;
		QString Sensor;
		QString Type;
		QString Slot;
	};

#endif
