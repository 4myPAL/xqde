/********************************************************************************
** Form generated from reading ui file 'XQDEUIConfigurator.ui'
**
** Created: Sun Apr 12 17:04:55 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_XQDEUICONFIGURATOR_H
#define UI_XQDEUICONFIGURATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XQDEUIConfigurator
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_2;
    QSlider *dockPositionX;
    QSlider *dockPositionY;
    QSlider *normalsize;
    QSlider *bigsize;
    QLabel *label_7;
    QLabel *label_3;
    QComboBox *dockposition;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QHBoxLayout *hboxLayout;
    QLabel *label_4;
    QPushButton *changeOverTextFont;
    QPushButton *changeOverTextColor;
    QCheckBox *autofit;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QWidget *tab_5;
    QVBoxLayout *vboxLayout1;
    QTabWidget *tabWidget_2;
    QWidget *tab_6;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout1;
    QPushButton *ic_path_add;
    QPushButton *ic_path_remove;
    QPushButton *ic_path_up;
    QPushButton *ic_path_down;
    QListView *listView;
    QWidget *tab_7;
    QVBoxLayout *vboxLayout3;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_12;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout1;
    QLabel *label_13;
    QComboBox *mod_minimized;
    QLabel *label_14;
    QComboBox *mod_multiwindow;
    QLabel *label_15;
    QComboBox *mod_tray;
    QLabel *label_16;
    QComboBox *mod_thumbnail;
    QLabel *label_17;
    QComboBox *mod_running;
    QWidget *tab_9;
    QVBoxLayout *vboxLayout4;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_19;
    QSpacerItem *verticalSpacer_5;
    QGridLayout *gridLayout2;
    QLabel *label_18;
    QComboBox *ani_new;
    QLabel *label_20;
    QComboBox *ani_remove;
    QWidget *tab_8;
    QVBoxLayout *vboxLayout5;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_21;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *hboxLayout2;
    QLabel *label_22;
    QComboBox *background_theme;
    QWidget *tab_4;
    QVBoxLayout *vboxLayout6;
    QLabel *label_9;
    QListWidget *listWidgets;
    QHBoxLayout *hboxLayout3;
    QLabel *label_10;
    QLineEdit *classNameWidget;
    QPushButton *lw_addWidget;
    QWidget *tab_3;
    QVBoxLayout *vboxLayout7;
    QLabel *label_6;
    QListWidget *list_plugin;
    QPushButton *list_plugin_configure;
    QLabel *label_5;

    void setupUi(QWidget *XQDEUIConfigurator)
    {
    if (XQDEUIConfigurator->objectName().isEmpty())
        XQDEUIConfigurator->setObjectName(QString::fromUtf8("XQDEUIConfigurator"));
    XQDEUIConfigurator->resize(519, 325);
    vboxLayout = new QVBoxLayout(XQDEUIConfigurator);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(9);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    tabWidget = new QTabWidget(XQDEUIConfigurator);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    gridLayout = new QGridLayout(tab_2);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    textBrowser = new QTextBrowser(tab_2);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

    gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

    tabWidget->addTab(tab_2, QString());
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    gridLayout_3 = new QGridLayout(tab);
    gridLayout_3->setSpacing(6);
    gridLayout_3->setMargin(11);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    gridLayout_2 = new QGridLayout();
    gridLayout_2->setSpacing(6);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    label_8 = new QLabel(tab);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

    label = new QLabel(tab);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout_2->addWidget(label, 3, 0, 1, 1);

    label_2 = new QLabel(tab);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout_2->addWidget(label_2, 4, 0, 1, 1);

    dockPositionX = new QSlider(tab);
    dockPositionX->setObjectName(QString::fromUtf8("dockPositionX"));
    dockPositionX->setMinimum(16);
    dockPositionX->setMaximum(256);
    dockPositionX->setSingleStep(8);
    dockPositionX->setPageStep(16);
    dockPositionX->setOrientation(Qt::Horizontal);

    gridLayout_2->addWidget(dockPositionX, 1, 1, 1, 1);

    dockPositionY = new QSlider(tab);
    dockPositionY->setObjectName(QString::fromUtf8("dockPositionY"));
    dockPositionY->setMinimum(16);
    dockPositionY->setMaximum(256);
    dockPositionY->setSingleStep(8);
    dockPositionY->setPageStep(16);
    dockPositionY->setValue(16);
    dockPositionY->setOrientation(Qt::Horizontal);

    gridLayout_2->addWidget(dockPositionY, 2, 1, 1, 1);

    normalsize = new QSlider(tab);
    normalsize->setObjectName(QString::fromUtf8("normalsize"));
    normalsize->setMinimum(16);
    normalsize->setMaximum(256);
    normalsize->setSingleStep(8);
    normalsize->setPageStep(16);
    normalsize->setOrientation(Qt::Horizontal);

    gridLayout_2->addWidget(normalsize, 3, 1, 1, 1);

    bigsize = new QSlider(tab);
    bigsize->setObjectName(QString::fromUtf8("bigsize"));
    bigsize->setMinimum(16);
    bigsize->setMaximum(256);
    bigsize->setSingleStep(8);
    bigsize->setPageStep(16);
    bigsize->setValue(16);
    bigsize->setOrientation(Qt::Horizontal);

    gridLayout_2->addWidget(bigsize, 4, 1, 1, 1);

    label_7 = new QLabel(tab);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

    label_3 = new QLabel(tab);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

    dockposition = new QComboBox(tab);
    dockposition->setObjectName(QString::fromUtf8("dockposition"));

    gridLayout_2->addWidget(dockposition, 0, 1, 1, 2);

    spinBox_6 = new QSpinBox(tab);
    spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));
    spinBox_6->setMinimum(-9999);
    spinBox_6->setMaximum(9999);

    gridLayout_2->addWidget(spinBox_6, 4, 2, 1, 1);

    spinBox_5 = new QSpinBox(tab);
    spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
    spinBox_5->setMinimum(-9999);
    spinBox_5->setMaximum(9999);

    gridLayout_2->addWidget(spinBox_5, 3, 2, 1, 1);

    spinBox = new QSpinBox(tab);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));
    spinBox->setMinimum(-9999);
    spinBox->setMaximum(9999);

    gridLayout_2->addWidget(spinBox, 2, 2, 1, 1);

    spinBox_2 = new QSpinBox(tab);
    spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
    spinBox_2->setMinimum(-9999);
    spinBox_2->setMaximum(9999);

    gridLayout_2->addWidget(spinBox_2, 1, 2, 1, 1);


    gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label_4 = new QLabel(tab);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout->addWidget(label_4);

    changeOverTextFont = new QPushButton(tab);
    changeOverTextFont->setObjectName(QString::fromUtf8("changeOverTextFont"));

    hboxLayout->addWidget(changeOverTextFont);

    changeOverTextColor = new QPushButton(tab);
    changeOverTextColor->setObjectName(QString::fromUtf8("changeOverTextColor"));

    hboxLayout->addWidget(changeOverTextColor);


    gridLayout_3->addLayout(hboxLayout, 2, 0, 1, 1);

    autofit = new QCheckBox(tab);
    autofit->setObjectName(QString::fromUtf8("autofit"));
    autofit->setEnabled(false);

    gridLayout_3->addWidget(autofit, 4, 0, 1, 1);

    line = new QFrame(tab);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout_3->addWidget(line, 3, 0, 1, 1);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

    tabWidget->addTab(tab, QString());
    tab_5 = new QWidget();
    tab_5->setObjectName(QString::fromUtf8("tab_5"));
    vboxLayout1 = new QVBoxLayout(tab_5);
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(11);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    tabWidget_2 = new QTabWidget(tab_5);
    tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
    tabWidget_2->setEnabled(false);
    tab_6 = new QWidget();
    tab_6->setObjectName(QString::fromUtf8("tab_6"));
    vboxLayout2 = new QVBoxLayout(tab_6);
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(11);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    ic_path_add = new QPushButton(tab_6);
    ic_path_add->setObjectName(QString::fromUtf8("ic_path_add"));

    hboxLayout1->addWidget(ic_path_add);

    ic_path_remove = new QPushButton(tab_6);
    ic_path_remove->setObjectName(QString::fromUtf8("ic_path_remove"));

    hboxLayout1->addWidget(ic_path_remove);

    ic_path_up = new QPushButton(tab_6);
    ic_path_up->setObjectName(QString::fromUtf8("ic_path_up"));

    hboxLayout1->addWidget(ic_path_up);

    ic_path_down = new QPushButton(tab_6);
    ic_path_down->setObjectName(QString::fromUtf8("ic_path_down"));

    hboxLayout1->addWidget(ic_path_down);


    vboxLayout2->addLayout(hboxLayout1);

    listView = new QListView(tab_6);
    listView->setObjectName(QString::fromUtf8("listView"));

    vboxLayout2->addWidget(listView);

    tabWidget_2->addTab(tab_6, QString());
    tab_7 = new QWidget();
    tab_7->setObjectName(QString::fromUtf8("tab_7"));
    vboxLayout3 = new QVBoxLayout(tab_7);
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(11);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(verticalSpacer_2);

    label_12 = new QLabel(tab_7);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    vboxLayout3->addWidget(label_12);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(verticalSpacer_3);

    gridLayout1 = new QGridLayout();
    gridLayout1->setSpacing(6);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    label_13 = new QLabel(tab_7);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    gridLayout1->addWidget(label_13, 0, 0, 1, 1);

    mod_minimized = new QComboBox(tab_7);
    mod_minimized->setObjectName(QString::fromUtf8("mod_minimized"));

    gridLayout1->addWidget(mod_minimized, 0, 1, 1, 1);

    label_14 = new QLabel(tab_7);
    label_14->setObjectName(QString::fromUtf8("label_14"));

    gridLayout1->addWidget(label_14, 1, 0, 1, 1);

    mod_multiwindow = new QComboBox(tab_7);
    mod_multiwindow->setObjectName(QString::fromUtf8("mod_multiwindow"));

    gridLayout1->addWidget(mod_multiwindow, 1, 1, 1, 1);

    label_15 = new QLabel(tab_7);
    label_15->setObjectName(QString::fromUtf8("label_15"));

    gridLayout1->addWidget(label_15, 2, 0, 1, 1);

    mod_tray = new QComboBox(tab_7);
    mod_tray->setObjectName(QString::fromUtf8("mod_tray"));

    gridLayout1->addWidget(mod_tray, 2, 1, 1, 1);

    label_16 = new QLabel(tab_7);
    label_16->setObjectName(QString::fromUtf8("label_16"));

    gridLayout1->addWidget(label_16, 3, 0, 1, 1);

    mod_thumbnail = new QComboBox(tab_7);
    mod_thumbnail->setObjectName(QString::fromUtf8("mod_thumbnail"));

    gridLayout1->addWidget(mod_thumbnail, 3, 1, 1, 1);

    label_17 = new QLabel(tab_7);
    label_17->setObjectName(QString::fromUtf8("label_17"));

    gridLayout1->addWidget(label_17, 4, 0, 1, 1);

    mod_running = new QComboBox(tab_7);
    mod_running->setObjectName(QString::fromUtf8("mod_running"));

    gridLayout1->addWidget(mod_running, 4, 1, 1, 1);


    vboxLayout3->addLayout(gridLayout1);

    tabWidget_2->addTab(tab_7, QString());
    tab_9 = new QWidget();
    tab_9->setObjectName(QString::fromUtf8("tab_9"));
    vboxLayout4 = new QVBoxLayout(tab_9);
    vboxLayout4->setSpacing(6);
    vboxLayout4->setMargin(11);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout4->addItem(verticalSpacer_4);

    label_19 = new QLabel(tab_9);
    label_19->setObjectName(QString::fromUtf8("label_19"));

    vboxLayout4->addWidget(label_19);

    verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout4->addItem(verticalSpacer_5);

    gridLayout2 = new QGridLayout();
    gridLayout2->setSpacing(6);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    label_18 = new QLabel(tab_9);
    label_18->setObjectName(QString::fromUtf8("label_18"));

    gridLayout2->addWidget(label_18, 0, 0, 1, 1);

    ani_new = new QComboBox(tab_9);
    ani_new->setObjectName(QString::fromUtf8("ani_new"));

    gridLayout2->addWidget(ani_new, 0, 1, 1, 1);

    label_20 = new QLabel(tab_9);
    label_20->setObjectName(QString::fromUtf8("label_20"));

    gridLayout2->addWidget(label_20, 1, 0, 1, 1);

    ani_remove = new QComboBox(tab_9);
    ani_remove->setObjectName(QString::fromUtf8("ani_remove"));

    gridLayout2->addWidget(ani_remove, 1, 1, 1, 1);


    vboxLayout4->addLayout(gridLayout2);

    tabWidget_2->addTab(tab_9, QString());
    tab_8 = new QWidget();
    tab_8->setObjectName(QString::fromUtf8("tab_8"));
    vboxLayout5 = new QVBoxLayout(tab_8);
    vboxLayout5->setSpacing(6);
    vboxLayout5->setMargin(11);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout5->addItem(verticalSpacer_7);

    label_21 = new QLabel(tab_8);
    label_21->setObjectName(QString::fromUtf8("label_21"));

    vboxLayout5->addWidget(label_21);

    verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout5->addItem(verticalSpacer_6);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_22 = new QLabel(tab_8);
    label_22->setObjectName(QString::fromUtf8("label_22"));

    hboxLayout2->addWidget(label_22);

    background_theme = new QComboBox(tab_8);
    background_theme->setObjectName(QString::fromUtf8("background_theme"));

    hboxLayout2->addWidget(background_theme);


    vboxLayout5->addLayout(hboxLayout2);

    tabWidget_2->addTab(tab_8, QString());

    vboxLayout1->addWidget(tabWidget_2);

    tabWidget->addTab(tab_5, QString());
    tab_4 = new QWidget();
    tab_4->setObjectName(QString::fromUtf8("tab_4"));
    vboxLayout6 = new QVBoxLayout(tab_4);
    vboxLayout6->setSpacing(6);
    vboxLayout6->setMargin(11);
    vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
    label_9 = new QLabel(tab_4);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    vboxLayout6->addWidget(label_9);

    listWidgets = new QListWidget(tab_4);
    listWidgets->setObjectName(QString::fromUtf8("listWidgets"));
    listWidgets->setDragEnabled(false);
    listWidgets->setDragDropMode(QAbstractItemView::NoDragDrop);
    listWidgets->setMovement(QListView::Static);
    listWidgets->setViewMode(QListView::IconMode);

    vboxLayout6->addWidget(listWidgets);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_10 = new QLabel(tab_4);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    hboxLayout3->addWidget(label_10);

    classNameWidget = new QLineEdit(tab_4);
    classNameWidget->setObjectName(QString::fromUtf8("classNameWidget"));

    hboxLayout3->addWidget(classNameWidget);

    lw_addWidget = new QPushButton(tab_4);
    lw_addWidget->setObjectName(QString::fromUtf8("lw_addWidget"));

    hboxLayout3->addWidget(lw_addWidget);


    vboxLayout6->addLayout(hboxLayout3);

    tabWidget->addTab(tab_4, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    vboxLayout7 = new QVBoxLayout(tab_3);
    vboxLayout7->setSpacing(6);
    vboxLayout7->setMargin(11);
    vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
    label_6 = new QLabel(tab_3);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    vboxLayout7->addWidget(label_6);

    list_plugin = new QListWidget(tab_3);
    list_plugin->setObjectName(QString::fromUtf8("list_plugin"));

    vboxLayout7->addWidget(list_plugin);

    list_plugin_configure = new QPushButton(tab_3);
    list_plugin_configure->setObjectName(QString::fromUtf8("list_plugin_configure"));

    vboxLayout7->addWidget(list_plugin_configure);

    tabWidget->addTab(tab_3, QString());

    vboxLayout->addWidget(tabWidget);

    label_5 = new QLabel(XQDEUIConfigurator);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    vboxLayout->addWidget(label_5);

    QWidget::setTabOrder(tabWidget, textBrowser);
    QWidget::setTabOrder(textBrowser, dockposition);
    QWidget::setTabOrder(dockposition, dockPositionX);
    QWidget::setTabOrder(dockPositionX, spinBox_2);
    QWidget::setTabOrder(spinBox_2, dockPositionY);
    QWidget::setTabOrder(dockPositionY, spinBox);
    QWidget::setTabOrder(spinBox, normalsize);
    QWidget::setTabOrder(normalsize, spinBox_5);
    QWidget::setTabOrder(spinBox_5, bigsize);
    QWidget::setTabOrder(bigsize, spinBox_6);
    QWidget::setTabOrder(spinBox_6, changeOverTextFont);
    QWidget::setTabOrder(changeOverTextFont, changeOverTextColor);
    QWidget::setTabOrder(changeOverTextColor, autofit);
    QWidget::setTabOrder(autofit, tabWidget_2);
    QWidget::setTabOrder(tabWidget_2, ic_path_add);
    QWidget::setTabOrder(ic_path_add, ic_path_remove);
    QWidget::setTabOrder(ic_path_remove, ic_path_up);
    QWidget::setTabOrder(ic_path_up, ic_path_down);
    QWidget::setTabOrder(ic_path_down, listView);
    QWidget::setTabOrder(listView, mod_minimized);
    QWidget::setTabOrder(mod_minimized, mod_multiwindow);
    QWidget::setTabOrder(mod_multiwindow, mod_tray);
    QWidget::setTabOrder(mod_tray, mod_thumbnail);
    QWidget::setTabOrder(mod_thumbnail, mod_running);
    QWidget::setTabOrder(mod_running, ani_new);
    QWidget::setTabOrder(ani_new, ani_remove);
    QWidget::setTabOrder(ani_remove, background_theme);
    QWidget::setTabOrder(background_theme, listWidgets);
    QWidget::setTabOrder(listWidgets, classNameWidget);
    QWidget::setTabOrder(classNameWidget, lw_addWidget);
    QWidget::setTabOrder(lw_addWidget, list_plugin);
    QWidget::setTabOrder(list_plugin, list_plugin_configure);

    retranslateUi(XQDEUIConfigurator);
    QObject::connect(dockPositionY, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(dockPositionX, SIGNAL(valueChanged(int)), spinBox_2, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), dockPositionY, SLOT(setValue(int)));
    QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), dockPositionX, SLOT(setValue(int)));
    QObject::connect(normalsize, SIGNAL(valueChanged(int)), spinBox_5, SLOT(setValue(int)));
    QObject::connect(spinBox_6, SIGNAL(valueChanged(int)), bigsize, SLOT(setValue(int)));
    QObject::connect(bigsize, SIGNAL(valueChanged(int)), spinBox_6, SLOT(setValue(int)));
    QObject::connect(spinBox_5, SIGNAL(valueChanged(int)), normalsize, SLOT(setValue(int)));

    tabWidget->setCurrentIndex(1);
    tabWidget_2->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(XQDEUIConfigurator);
    } // setupUi

    void retranslateUi(QWidget *XQDEUIConfigurator)
    {
    XQDEUIConfigurator->setWindowTitle(QApplication::translate("XQDEUIConfigurator", "XQDE configuration tool", 0, QApplication::UnicodeUTF8));
    textBrowser->setHtml(QApplication::translate("XQDEUIConfigurator", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">Hello! I am XQDE</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">The XIA Projects Desktop Environment</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">This is an alpha preview of XQDE: the K"
        "XDocker evolution.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">XQDE is new idea for</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">- task manager</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">- manage desktop icons (when ready)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">- desktop environment (when ready)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; "
        "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe Media Center'; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">XQDE depends on:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">- Trolltech Qt 4.2.x</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">- X11</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">no more other libraries.</span></p>\n"
"<p style=\""
        " margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">- Composite extensions (AIGLX or XGL, either with a composite manager)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe Media Center'; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">XQDE is GPL opensource XIA Projects 2009 product, you can help us sending money or themes ;)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe Media Center'; font-size:10pt;\">Thanks you to try it, Stefano Zingarini xqde@xiaprojects.com</span></p>\n"
""
        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe Media Center'; font-size:10pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("XQDEUIConfigurator", "About", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("XQDEUIConfigurator", "Vertical", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("XQDEUIConfigurator", "Normal size", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("XQDEUIConfigurator", "Big size", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("XQDEUIConfigurator", "Horizontal", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("XQDEUIConfigurator", "Position", 0, QApplication::UnicodeUTF8));
    dockposition->clear();
    dockposition->insertItems(0, QStringList()
     << QApplication::translate("XQDEUIConfigurator", "bottom", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("XQDEUIConfigurator", "top", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("XQDEUIConfigurator", "left", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("XQDEUIConfigurator", "right", 0, QApplication::UnicodeUTF8)
    );
    label_4->setText(QApplication::translate("XQDEUIConfigurator", "Text near icon", 0, QApplication::UnicodeUTF8));
    changeOverTextFont->setText(QApplication::translate("XQDEUIConfigurator", "Set text font", 0, QApplication::UnicodeUTF8));
    changeOverTextColor->setText(QApplication::translate("XQDEUIConfigurator", "Set text color", 0, QApplication::UnicodeUTF8));
    autofit->setText(QApplication::translate("XQDEUIConfigurator", "Autofit the dock on the screen", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("XQDEUIConfigurator", "Design", 0, QApplication::UnicodeUTF8));
    ic_path_add->setText(QApplication::translate("XQDEUIConfigurator", "Add", 0, QApplication::UnicodeUTF8));
    ic_path_remove->setText(QApplication::translate("XQDEUIConfigurator", "Remove", 0, QApplication::UnicodeUTF8));
    ic_path_up->setText(QApplication::translate("XQDEUIConfigurator", "Up", 0, QApplication::UnicodeUTF8));
    ic_path_down->setText(QApplication::translate("XQDEUIConfigurator", "Down", 0, QApplication::UnicodeUTF8));
    tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("XQDEUIConfigurator", "Icons Paths", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("XQDEUIConfigurator", "Look on plugins page to configure addons", 0, QApplication::UnicodeUTF8));
    label_13->setText(QApplication::translate("XQDEUIConfigurator", "Minimized task", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("XQDEUIConfigurator", "Multi window task", 0, QApplication::UnicodeUTF8));
    label_15->setText(QApplication::translate("XQDEUIConfigurator", "Tray or hidden task", 0, QApplication::UnicodeUTF8));
    label_16->setText(QApplication::translate("XQDEUIConfigurator", "Thumbnail", 0, QApplication::UnicodeUTF8));
    label_17->setText(QApplication::translate("XQDEUIConfigurator", "Running light", 0, QApplication::UnicodeUTF8));
    tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QApplication::translate("XQDEUIConfigurator", "Mods", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("XQDEUIConfigurator", "Look on plugins page to configure addons", 0, QApplication::UnicodeUTF8));
    label_18->setText(QApplication::translate("XQDEUIConfigurator", "New task", 0, QApplication::UnicodeUTF8));
    label_20->setText(QApplication::translate("XQDEUIConfigurator", "Removing task", 0, QApplication::UnicodeUTF8));
    tabWidget_2->setTabText(tabWidget_2->indexOf(tab_9), QApplication::translate("XQDEUIConfigurator", "Animations", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("XQDEUIConfigurator", "Look on plugins page to configure addons", 0, QApplication::UnicodeUTF8));
    label_22->setText(QApplication::translate("XQDEUIConfigurator", "Theme", 0, QApplication::UnicodeUTF8));
    tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QApplication::translate("XQDEUIConfigurator", "Backgrounds", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("XQDEUIConfigurator", "Themes", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("XQDEUIConfigurator", "Select Widget to get more info", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("XQDEUIConfigurator", "className", 0, QApplication::UnicodeUTF8));
    lw_addWidget->setText(QApplication::translate("XQDEUIConfigurator", "Add", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("XQDEUIConfigurator", "Widgets", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("XQDEUIConfigurator", "Plugins loaded", 0, QApplication::UnicodeUTF8));
    list_plugin_configure->setText(QApplication::translate("XQDEUIConfigurator", "Configure", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("XQDEUIConfigurator", "Plugins", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("XQDEUIConfigurator", "XQDE is a XIA Projects 2009 product xqde@xiaprojects.com", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(XQDEUIConfigurator);
    } // retranslateUi

};

namespace Ui {
    class XQDEUIConfigurator: public Ui_XQDEUIConfigurator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XQDEUICONFIGURATOR_H
