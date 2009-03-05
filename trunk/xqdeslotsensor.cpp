//
// C++ Implementation: xqdeslotsensor
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QDomElement>

#include "xqdeslotsensor.h"

QDomElement &XQDESlotSensor::writeXMLElement(class QDomElement &pXML)
{
	pXML.setAttribute("value",Slot);
	pXML.setAttribute("type",Type);
	pXML.setAttribute("sensor",Sensor);
	pXML.setAttribute("counter",(uint)Counter);
	return pXML;
}
QDomElement &XQDESlotSensor::readXMLElement(class QDomElement &pXML)
{
	Slot=pXML.attribute("value");
	Type=pXML.attribute("type");
	Sensor=pXML.attribute("sensor");
	Counter=pXML.attribute("counter").toInt();
	return pXML;
}
