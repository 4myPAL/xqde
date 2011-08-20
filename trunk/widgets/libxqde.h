#ifndef LIBXQDEINCLUDES
#define LIBXQDEINCLUDES

#include <QtPlugin>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEPluginInterface
{
public:
//	XQDEPluginInterface(QObject *parent = 0);
	virtual ~XQDEPluginInterface();
	virtual QObject * Respawn(QObject *p);
};

Q_DECLARE_INTERFACE(XQDEPluginInterface,
		    "XQDE.XQDEPluginInterface/1.0")
#endif
 
