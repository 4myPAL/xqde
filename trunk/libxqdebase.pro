# File generato dal gestore qmake di KDevelop.
# -------------------------------------------
# Sottocartella relativa alla cartella principale del progetto: .
# Il target è un'applicazione:
FORMS += XQDEUIIcon.ui \
    XQDEUIConfigurator.ui \
    XQDEUIConfiguratorXML.ui
HEADERS += libxqdebase.h \
    xqdeclass.h \
    xqdeenvironment.h \
    xqdemain.h \
    xqderoot.h \
    xquniqueapplication.h \
    xqwidget.h \
    xqdesensor_systemtray.h \
    xqdesensor_zoomengine.h \
    xqtext.h \
    xqderuler.h \
    xqwfirsthand.h \
    xqdesensor_taskmanager.h \
    xqde.h \
    xqdebasket.h \
    xqdeicon.h \
    xqdeuiiconwindow.h \
    xqdeaction.h \
    xqdeslotsensor.h \
    xqdeanimation.h \
    xqdeconfigurator.h \
    xqdeconfiguratorxml.h \
    xqwfirsthand_bottom.h \
    xqdeplugin.h \
    xqdeplugin_analogclock.h \
    xqdeproxy.h \
    xqdeplugin_webhelper.h \
    xqdeio.h \
    xqdeinterface.h \
    xqimage.h \
    import_netwm.h \
    xqdedevice.h \
    xqdewindowmanagerinterface.h \
    xqdesystray.h \
    xqdeinterface.h
SOURCES += libxqdebase.cpp \
    main.cpp \
    xqdeclass.cpp \
    xqdeenvironment.cpp \
    xqdemain.cpp \
    xqderoot.cpp \
    xquniqueapplication.cpp \
    xqwidget.cpp \
    xqdesensor_systemtray.cpp \
    xqdesensor_zoomengine.cpp \
    xqtext.cpp \
    xqderuler.cpp \
    xqwfirsthand.cpp \
    xqdesensor_taskmanager.cpp \
    xqdebasket.cpp \
    xqdeicon.cpp \
    xqdeuiiconwindow.cpp \
    xqdeaction.cpp \
    xqdeslotsensor.cpp \
    xqdeanimation.cpp \
    xqdeconfigurator.cpp \
    xqdeconfiguratorxml.cpp \
    xqwfirsthand_bottom.cpp \
    xqdeplugin.cpp \
    xqdeplugin_analogclock.cpp \
    xqdeproxy.cpp \
    xqdeplugin_webhelper.cpp \
    xqdeio.cpp \
    xqimage.cpp \
    import_netwm.cpp \
    xqdedevice.cpp \
    xqdewindowmanagerinterface.cpp \
    xqdesystray.cpp
TRANSLATIONS = xqde_it.ts
TEMPLATE = app
LIBS += -lXcomposite\
	-lXdamage
QT += network \
    xml \
    dbus
RESOURCES += resources/libxqdebase.qrc
DEFINES += QT_NO_DEBUG_OUTPUT
#QT_NO_WARNING_OUTPUT
