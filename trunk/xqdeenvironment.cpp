//
// C++ Implementation: xqdeenvironment
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QImage>
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QtDebug>
#include <QStringList>
#include <QDomElement>
#include <QObject>
#include <QDirIterator>

#include "xqdeenvironment.h"
#include "xqdeconfiguratorxml.h"
#include "xqde.h"

/*
XQDEEnvironmentUserProfile 	XQDEEnvironment::UserProfile;
XQDEEnvironmentTheme 		XQDEEnvironment::Theme;
XQDEEnvironmentGUI		XQDEEnvironment::GUI;
*/


/*
QMap <QString,long> 		XQDEEnvironment::Longs;
QMap <QString,QString> 		XQDEEnvironment::Strings;
QMap <QString,QStringList> 	XQDEEnvironment::Lists;
*/
XQDEEnvironment::XQDEEnvironment *DesktopEnvironment;


QImage *XQDE_ImageSetIntensity(QImage &lavoro,double i)
{
	lavoro=lavoro.convertToFormat(QImage::Format_ARGB32);
//	lavoro.setAlphaBuffer(true);
	uint width=lavoro.width();
	uint height=lavoro.height();
	for(uint x=0;x<height;x++)
	{
		unsigned  int *riga=(unsigned int *)lavoro.scanLine(x);
		for(uint y=0;y<width;y++)
		{
			//0xAARRGGBB
                        riga[y]=(riga[y]&0x00FFFFFF)+(((unsigned int)((double)i*(double)(riga[y]>>24)))<<24);
                        /*
			uint alfa=qAlpha(*p);
			alfa=uint(alfa*i);
			*p =qRgba(qRed(*p),qGreen(*p),qBlue(*p),alfa);
                        */
		}
	}
	return &lavoro;

}


QImage *XQDE_ImageCopyRop(const QImage &source, QImage &dest, uint sx, uint sy, uint sz)
{
	//uint esz=sy+sz;
	uint dx=sx;
	for(uint y=0;y<sz;y++)
	{
		uint *riga=(uint *)source.scanLine(y);
		uint *rigadest=(uint *)dest.scanLine(y+sy);
		memcpy(rigadest+dx,riga,sizeof(uint)*sz);
	}
	
	return &dest;
}

QImage *XQDE_ImageEraseRect(QImage &lavoro,uint sx,uint sy,uint sz)
{
//	uint width=lavoro.width();
//	uint height=lavoro.height();
	uint esz=sy+sz;
	uint dx=sx;
	for(uint y=sy;y<esz;y++)
	{
		uint *riga=(uint *)lavoro.scanLine(y);
		memset(riga+dx,0,sizeof(uint)*sz);
	}
	
	return &lavoro;
}

#ifndef RESIZEVIAXRENDER
QImage *XQDE_ImageReflectBottom(QImage &xImgSource,QImage &newImage)
#else
QImage *XQDE_ImageReflectBottom(QPixmap &xImgSource,QImage &newImage)
#endif
{
//	uint rHeight=xImgSource.height();
//	uint rWidth=xImgSource.width();
//
//	newImage=QImage(rWidth,rHeight,QImage::Format_ARGB32);
//	newImage.fill(Qt::transparent);
//
//	QPainter p;
//	p.begin(&newImage);
//	p.drawPixmap(0,0,xImgSource);
//	p.end();
//
//	newImage=newImage.mirrored();
//
//
//	double i=0.7;
//	double ki=i/rHeight;
//
//	for(uint hri=0;hri<rHeight;hri++)
//	{
//		uint *riga=(uint *)newImage.scanLine(hri);
//			for(uint y=0;y<rWidth;y++)
//			{
//				//0xAARRGGBB
//                                riga[y]=(riga[y]&0x00FFFFFF)+(((unsigned int)((double)(i-ki*hri)*(double)(riga[y]>>24)))<<24);
//			}
//	}
//	return &newImage;

        #ifndef RESIZEVIAXRENDER
        newImage=xImgSource.mirrored();
        #else
        newImage=xImgSource.toImage().mirrored();
        #endif

// dont'work
//        qreal opacityFactor = 1;
//
//        // Add gradient to the reflection
//        QLinearGradient gradient(QPointF(0, 0), QPointF(0, newImage.height()*0.25));
//        gradient.setColorAt(0, QColor(0, 0, 0, 150));
//        gradient.setColorAt(1, Qt::transparent);
//
//        QPainter reflectionPainter(&newImage);
//        reflectionPainter.save();
//        reflectionPainter.setOpacity(opacityFactor);
//        reflectionPainter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
//        reflectionPainter.fillRect(0, 0, newImage.width(), newImage.height(), gradient);
//        reflectionPainter.restore();
//        reflectionPainter.end();

        double i=0.7;
        double ki=i/ newImage.height();

        for(uint hri=0;hri< newImage.height();hri++)
        {
                uint *riga=(uint *)newImage.scanLine(hri);
                        for(uint y=0;y<newImage.width();y++)
                        {
                                //0xAARRGGBB
                                riga[y]=(riga[y]&0x00FFFFFF)+(((unsigned int)((double)(i-ki*hri)*(double)(riga[y]>>24)))<<24);
                        }
        }
        return &newImage;

}

QImage *XQDE_ImageRepeat(QImage &xImgSource,QImage &newImage, int rWidth,int rHeight)
{
	//QImage newImage;
	xImgSource=xImgSource.convertToFormat(QImage::Format_ARGB32);
	newImage=QImage(rWidth,rHeight,QImage::Format_ARGB32);
        newImage.fill(Qt::transparent);
	int tw=xImgSource.width();
	int th=xImgSource.height();
	int cy=((rHeight+(rHeight%th))/th);
	int cx=((rWidth+(rWidth%tw))/tw);
	QPainter p;
	p.begin(&newImage);

	for(int wy=0;wy<cy;wy++)
	{
		for(int wx=0;wx<cx;wx++)
		{
			p.drawImage(wx*tw,wy*th,xImgSource);
		}
	}
	p.end();
	return &newImage;
}

void XQDEEnvironmentGUI::store(QDomNode *e)
{
e->toElement().setAttribute("handIconsMax",(int)handIconsMax);
e->toElement().setAttribute("sizeIconsMax",(int)sizeIconsMax);
e->toElement().setAttribute("sizeIconsNormal",(int)sizeIconsNormal);
e->toElement().setAttribute("task_GroupSimilarWindows",(int)task_GroupSimilarWindows);
e->toElement().setAttribute("updateViaDND",(int)updateViaDND);
e->toElement().setAttribute("desktopFont.FontRed",(int)desktopFont.FontRed);
e->toElement().setAttribute("desktopFont.FontGreen",(int)desktopFont.FontGreen);
e->toElement().setAttribute("desktopFont.FontBlue",(int)desktopFont.FontBlue);
e->toElement().setAttribute("desktopFont.FontFamily",desktopFont.FontFamily);
e->toElement().setAttribute("desktopFont.FontSize",(int)desktopFont.FontSize);
e->toElement().setAttribute("desktopFont.BackgroundPath",desktopFont.BackgroundPath);
e->toElement().setAttribute("desktopFont.OtherBinaryValue",(int)desktopFont.OtherBinaryValue);
e->toElement().setAttribute("desktopFont.Weight",(int)desktopFont.Weight);
e->toElement().setAttribute("desktopFont.Other",(int)desktopFont.Other);
e->toElement().setAttribute("desktopFont.Alias",desktopFont.Alias);
e->toElement().setAttribute("desktopFont.XPercentageDisplacement",(int)desktopFont.XPercentageDisplacement);
e->toElement().setAttribute("desktopFont.YPercentageDisplacement",(int)desktopFont.YPercentageDisplacement);
e->toElement().setAttribute("dockAlign",(int)dockAlign);
e->toElement().setAttribute("dockAlignDisplaceX",(int)dockAlignDisplaceX);
e->toElement().setAttribute("dockAlignDisplaceY",(int)dockAlignDisplaceY);
}

void XQDEEnvironmentGUI::restore(QDomNode *e)
{
handIconsMax=e->toElement().attribute("handIconsMax",QString::number(handIconsMax)).toInt();
sizeIconsMax=e->toElement().attribute("sizeIconsMax",QString::number(sizeIconsMax)).toInt();
sizeIconsNormal=e->toElement().attribute("sizeIconsNormal",QString::number(sizeIconsNormal)).toInt();
task_GroupSimilarWindows=e->toElement().attribute("task_GroupSimilarWindows",QString::number(task_GroupSimilarWindows)).toInt();
updateViaDND=e->toElement().attribute("updateViaDND",QString::number(updateViaDND)).toInt();
desktopFont.FontRed=e->toElement().attribute("desktopFont.FontRed",QString::number(desktopFont.FontRed)).toInt();
desktopFont.FontGreen=e->toElement().attribute("desktopFont.FontGreen",QString::number(desktopFont.FontGreen)).toInt();
desktopFont.FontBlue=e->toElement().attribute("desktopFont.FontBlue",QString::number(desktopFont.FontBlue)).toInt();
desktopFont.FontSize=e->toElement().attribute("desktopFont.FontSize",QString::number(desktopFont.FontSize)).toInt();
desktopFont.OtherBinaryValue=e->toElement().attribute("desktopFont.OtherBinaryValue",QString::number(desktopFont.OtherBinaryValue)).toInt();
desktopFont.Weight=e->toElement().attribute("desktopFont.Weight",QString::number(desktopFont.Weight)).toInt();
desktopFont.Other=e->toElement().attribute("desktopFont.Other",QString::number(desktopFont.Other)).toInt();
desktopFont.XPercentageDisplacement=e->toElement().attribute("desktopFont.XPercentageDisplacement",QString::number(desktopFont.XPercentageDisplacement)).toInt();
desktopFont.YPercentageDisplacement=e->toElement().attribute("desktopFont.YPercentageDisplacement",QString::number(desktopFont.YPercentageDisplacement)).toInt();
dockAlign=e->toElement().attribute("dockAlign",QString::number(dockAlign)).toInt();
dockAlignDisplaceX=e->toElement().attribute("dockAlignDisplaceX",QString::number(dockAlignDisplaceX)).toInt();
dockAlignDisplaceY=e->toElement().attribute("dockAlignDisplaceY",QString::number(dockAlignDisplaceY)).toInt();
//xxxx=e->toElement().attribute("xxxx",QString::number(xxx)).toInt();

desktopFont.FontFamily=e->toElement().attribute("desktopFont.FontFamily",desktopFont.FontFamily);
desktopFont.BackgroundPath=e->toElement().attribute("desktopFont.BackgroundPath",desktopFont.BackgroundPath);
desktopFont.Alias=e->toElement().attribute("desktopFont.Alias",desktopFont.Alias);
}

XQDEEnvironmentGUI::XQDEEnvironmentGUI()
{
        handIconsMax=32;
        sizeIconsMax=74;
        sizeIconsNormal=32;
        task_GroupSimilarWindows=0;
        updateViaDND=1;
        desktopFont.FontRed=36;
        desktopFont.FontGreen=36;
        desktopFont.FontBlue=36;
        desktopFont.FontFamily="DejaVu Sans";
        desktopFont.FontSize=10;
        desktopFont.BackgroundPath="";
        desktopFont.Bold=false;
        desktopFont.Italic=false;
        desktopFont.OtherBinaryValue=0;
        desktopFont.Weight=50;
        desktopFont.Other=0;
        desktopFont.Alias="";
        desktopFont.XPercentageDisplacement=0;

        desktopFont.YPercentageDisplacement=0;


        // 0 bottom
        // 1 top
        // 2 left
        // 3 right
        dockAlign=0;

        dockAlignDisplaceX=0;
        dockAlignDisplaceY=0;
        task_GroupByPID=1;
}

void GenericPluginNeedPolledEnable()
{
	DesktopEnvironment->GenericPluginNeedPolled=1;
}

XQDEEnvironment::XQDEEnvironment(XQDEClass *)
// : XQDEClass(parent)
{
	GenericPluginNeedPolled=0;
}

XQDEEnvironment::~XQDEEnvironment()
{
}

XQDEEnvironmentUserProfile::XQDEEnvironmentUserProfile()
{
	ConfiguratorXML=(QWidget *)new XQDEConfiguratorXML();
	
	connect(this, SIGNAL(configureThisComponentViaXML(QObject *)),ConfiguratorXML,SLOT(configureThisComponentViaXML(QObject *)));
	
	emit configureThisComponentViaXML(NULL);
}


void XQDEEnvironmentUserProfile::configureComponent(QObject *remoteObj)
{
	emit configureThisComponentViaXML(remoteObj);
}


extern QString DataPath;
extern QString EXEPath;

XQDEEnvironmentTheme::XQDEEnvironmentTheme():QObject(NULL)
{
	Theme="default";
	IconsPaths=new QStringList();
}

void XQDEEnvironmentTheme::store(QDomNode *e)
{
e->toElement().setAttribute("ThemeName",Theme);
}

void XQDEEnvironmentTheme::restore(QDomNode *e)
{
Theme=e->toElement().attribute("ThemeName").toAscii().data();
}

void XQDEEnvironmentTheme::xReset()
{
	//Theme="default";
	pathImages=getPathImagesByTheme(Theme);
	IconsPaths->clear();
	if(DataPath!="")
	{
		IconsPaths->append(getPathImagesByTheme(Theme));
		IconsPaths->append(DataPath+"/.xqde/icons");
	}


	IconsPaths->append(getPathImagesByTheme(Theme,1));
	IconsPaths->append(QDir::home().path()+"/.xqde/icons");

	if(EXEPath!="")
	{
		IconsPaths->append(getPathImagesByTheme(Theme,2));
		IconsPaths->append(EXEPath+"/.xqde/icons");
		IconsPaths->append(getPathImagesByTheme("default",2));
		IconsPaths->append(EXEPath+"/../share/xqde/icons");
	}
	else
	{
		IconsPaths->append(getPathImagesByTheme("default",2));
		//IconsPaths->append("/usr/share/xqde/icons");
	}



	//IconsPaths->append(Theme);
	Arrow="arrow.png";
	

	qWarning("Icons path are:");
	for(int ifl=0;ifl<IconsPaths->count();ifl++)
	{
                qWarning("Icon path are: %s",IconsPaths->at(ifl).toAscii().data());
	}
	
	checkDefaultResourcesConsistency();
}

QString XQDEEnvironmentTheme::getPathImagesByTheme(QString ThisTheme, int UserLevel)
{
	// 0 DataPath || home
	// 1 home
	// 2 INSTALL PREFIX
	if(ThisTheme=="")ThisTheme="default";
	QString rit="";
	switch(UserLevel)
	{
		case 0:
			if(DataPath!="")rit=DataPath+"/.xqde/themes/"+ThisTheme+"/";
			else rit=QDir::home().path()+"/.xqde/themes/"+ThisTheme+"/";
			break;
		case 1:
			rit=QDir::home().path()+"/.xqde/themes/"+ThisTheme+"/";
			break;
		case 2:
			// TODO: install prefix
			if(EXEPath!="")rit=EXEPath+"/../share/xqde/themes"+ThisTheme+"/";
			else rit="../share/xqde/themes"+ThisTheme+"/";
			break;
		default:
			qWarning("QString XQDEEnvironmentTheme::getPathImagesByTheme(QString ThisTheme, int UserLevel) unknown userlevel");
	}
	return rit;
}

void XQDEEnvironmentTheme::checkDefaultResourcesConsistency()
{
	// this will check if you have correctly set datapaths
	QDir test1(pathImages);
	if(test1.exists())
	{
		// we can test only if the directory exists because we may not need arrows or backgrounds
	}
	else emit XQDEEnvironmentTheme_findResources_miss(Theme,pathImages);
}


QString XQDEEnvironmentTheme::findImage(QString logicName)
{
	QString imgFileNameLogic=logicName;
	QString imgFileNameReal;
	QFile ifr(logicName);
	qWarning()<<logicName;
	if(ifr.exists())
	{
                qDebug()<<"XQDEEnvironmentTheme::findImage(QString "<<logicName<<") = "<<logicName;
		return logicName;
	}
	
	
	for(int ifl=0;ifl<IconsPaths->count();ifl++)
	{
		// PNG
		imgFileNameReal=IconsPaths->at(ifl);
		//imgFileNameReal=imgFileNameReal;
		imgFileNameReal=imgFileNameReal+"/";
		imgFileNameReal=imgFileNameReal+imgFileNameLogic;
		imgFileNameReal=imgFileNameReal+".png";
		ifr.setFileName(imgFileNameReal);
		if(ifr.exists() && imgFileNameReal!=QString::null)break;
		
		// SVG
		imgFileNameReal=IconsPaths->at(ifl);
		//imgFileNameReal=imgFileNameReal;
		imgFileNameReal=imgFileNameReal+"/";
		imgFileNameReal=imgFileNameReal+imgFileNameLogic;
		imgFileNameReal=imgFileNameReal+".svg";
		ifr.setFileName(imgFileNameReal);
		if(ifr.exists() && imgFileNameReal!=QString::null)break;

		// 0.36 all *
		imgFileNameReal=IconsPaths->at(ifl);
		//imgFileNameReal=imgFileNameReal;
		imgFileNameReal=imgFileNameReal+"/";
		imgFileNameReal=imgFileNameReal+imgFileNameLogic;
		ifr.setFileName(imgFileNameReal);
		if(ifr.exists() && imgFileNameReal!=QString::null)break;
	}
	if(ifr.exists() && imgFileNameReal!=QString::null)
	{
                qDebug()<<"XQDEEnvironmentTheme::findImage(QString logicName) = "<<logicName;
		return imgFileNameReal;
	}
        qDebug()<<"XQDEEnvironmentTheme::findImage(QString "<<logicName<<") = "<<"!!!Nothing!!!";
	emit XQDEEnvironmentTheme_findImage_miss(logicName);
	
		imgFileNameReal=QDir::home().path()+"/.xqde/icons";
		imgFileNameReal=imgFileNameReal+"/";
		imgFileNameReal=imgFileNameReal+imgFileNameLogic;
		imgFileNameReal=imgFileNameReal+".png";
		ifr.setFileName(imgFileNameReal);
		if(ifr.exists() && imgFileNameReal!=QString::null)return imgFileNameReal;

	return "";
}

QStringList XQDEEnvironmentTheme::findThemesName()
{
    QStringList ThemesListName;
    QString     directory_path="";

    //Themes main directory path
    directory_path=QDir::home().path()+"/.xqde/themes/";

    // Then create an instance of our QDirIterator, which takes as parameters
    // the directory, a QDir filter and an option flag which the QDirIterator is told
    // to go on the subdirectories also.
    // I have combined the QDir filters to list directory without special entries "." and ".."

    QDirIterator directory_walker(directory_path, QDir::Dirs | QDir::NoDotAndDotDot); //| QDir::NoSymLinks

    // QDirIterator object has a boolean method called hasNext() which returns true
    // if the directory have more files, false otherwise and based on that information,
    // we can write a while loop like the one below

    while(directory_walker.hasNext())
    {
	// then we tell our directory_walker object to explicitly take next element until the loop finishes
	directory_walker.next();

	// This is a Theme directory save it
	ThemesListName << directory_walker.fileName().toAscii().data();
    }


    return ThemesListName;

}
