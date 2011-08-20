//ToDo interface for plugins

class QString;
class QStringList;
class QObject;

class XQDEWidgetInterface
{
public:
    virtual ~XQDEWidgetInterface() {}
//    virtual QString getWidgetName ();
    virtual QStringList effects() const = 0;
//    virtual void attach(QObject *newI);


};

Q_DECLARE_INTERFACE(XQDEWidgetInterface, "com.XQDE.Plugin.XQDEWidgetInterface/1.0")
