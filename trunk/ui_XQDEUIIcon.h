/********************************************************************************
** Form generated from reading ui file 'XQDEUIIcon.ui'
**
** Created: Fri Feb 27 23:48:04 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_XQDEUIICON_H
#define UI_XQDEUIICON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XQDEUIIcon
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    QCheckBox *skipFeature;
    QHBoxLayout *hboxLayout;
    QLineEdit *uniquename;
    QLabel *label;
    QCheckBox *keepindock;
    QCheckBox *groupwindows;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout1;
    QLineEdit *defaulticon;
    QLabel *label_2;
    QCheckBox *enablepreview;
    QCheckBox *enableIconFromWindow;
    QWidget *tab_3;
    QVBoxLayout *vboxLayout3;
    QGroupBox *groupBox;
    QHBoxLayout *hboxLayout2;
    QLineEdit *useractionclicksx;
    QLabel *label_3;
    QWidget *tab_4;
    QVBoxLayout *vboxLayout4;
    QLabel *label_4;
    QListWidget *slotsSensor;
    QHBoxLayout *hboxLayout3;
    QLineEdit *sl;
    QPushButton *addsl;
    QPushButton *delsl;
    QHBoxLayout *hboxLayout4;
    QPushButton *bSaveAsTemplate;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *XQDEUIIcon)
    {
    if (XQDEUIIcon->objectName().isEmpty())
        XQDEUIIcon->setObjectName(QString::fromUtf8("XQDEUIIcon"));
    XQDEUIIcon->resize(464, 252);
    vboxLayout = new QVBoxLayout(XQDEUIIcon);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setMargin(9);
#endif
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    tabWidget = new QTabWidget(XQDEUIIcon);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    vboxLayout1 = new QVBoxLayout(tab);
#ifndef Q_OS_MAC
    vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout1->setMargin(9);
#endif
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    skipFeature = new QCheckBox(tab);
    skipFeature->setObjectName(QString::fromUtf8("skipFeature"));

    vboxLayout1->addWidget(skipFeature);

    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    uniquename = new QLineEdit(tab);
    uniquename->setObjectName(QString::fromUtf8("uniquename"));
    uniquename->setMinimumSize(QSize(250, 0));

    hboxLayout->addWidget(uniquename);

    label = new QLabel(tab);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);


    vboxLayout1->addLayout(hboxLayout);

    keepindock = new QCheckBox(tab);
    keepindock->setObjectName(QString::fromUtf8("keepindock"));

    vboxLayout1->addWidget(keepindock);

    groupwindows = new QCheckBox(tab);
    groupwindows->setObjectName(QString::fromUtf8("groupwindows"));

    vboxLayout1->addWidget(groupwindows);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    vboxLayout2 = new QVBoxLayout(tab_2);
#ifndef Q_OS_MAC
    vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout2->setMargin(9);
#endif
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout1->setMargin(0);
#endif
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    defaulticon = new QLineEdit(tab_2);
    defaulticon->setObjectName(QString::fromUtf8("defaulticon"));
    defaulticon->setMinimumSize(QSize(250, 0));

    hboxLayout1->addWidget(defaulticon);

    label_2 = new QLabel(tab_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout1->addWidget(label_2);


    vboxLayout2->addLayout(hboxLayout1);

    enablepreview = new QCheckBox(tab_2);
    enablepreview->setObjectName(QString::fromUtf8("enablepreview"));

    vboxLayout2->addWidget(enablepreview);

    enableIconFromWindow = new QCheckBox(tab_2);
    enableIconFromWindow->setObjectName(QString::fromUtf8("enableIconFromWindow"));

    vboxLayout2->addWidget(enableIconFromWindow);

    tabWidget->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    vboxLayout3 = new QVBoxLayout(tab_3);
#ifndef Q_OS_MAC
    vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout3->setMargin(9);
#endif
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    groupBox = new QGroupBox(tab_3);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    hboxLayout2 = new QHBoxLayout(groupBox);
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout2->setMargin(9);
#endif
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    useractionclicksx = new QLineEdit(groupBox);
    useractionclicksx->setObjectName(QString::fromUtf8("useractionclicksx"));
    useractionclicksx->setMinimumSize(QSize(250, 0));

    hboxLayout2->addWidget(useractionclicksx);

    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout2->addWidget(label_3);


    vboxLayout3->addWidget(groupBox);

    tabWidget->addTab(tab_3, QString());
    tab_4 = new QWidget();
    tab_4->setObjectName(QString::fromUtf8("tab_4"));
    vboxLayout4 = new QVBoxLayout(tab_4);
#ifndef Q_OS_MAC
    vboxLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout4->setMargin(9);
#endif
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    label_4 = new QLabel(tab_4);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    vboxLayout4->addWidget(label_4);

    slotsSensor = new QListWidget(tab_4);
    slotsSensor->setObjectName(QString::fromUtf8("slotsSensor"));

    vboxLayout4->addWidget(slotsSensor);

    hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout3->setSpacing(6);
#endif
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    sl = new QLineEdit(tab_4);
    sl->setObjectName(QString::fromUtf8("sl"));
    sl->setMinimumSize(QSize(250, 0));

    hboxLayout3->addWidget(sl);

    addsl = new QPushButton(tab_4);
    addsl->setObjectName(QString::fromUtf8("addsl"));

    hboxLayout3->addWidget(addsl);

    delsl = new QPushButton(tab_4);
    delsl->setObjectName(QString::fromUtf8("delsl"));

    hboxLayout3->addWidget(delsl);


    vboxLayout4->addLayout(hboxLayout3);

    tabWidget->addTab(tab_4, QString());

    vboxLayout->addWidget(tabWidget);

    hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout4->setSpacing(6);
#endif
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    bSaveAsTemplate = new QPushButton(XQDEUIIcon);
    bSaveAsTemplate->setObjectName(QString::fromUtf8("bSaveAsTemplate"));

    hboxLayout4->addWidget(bSaveAsTemplate);

    buttonBox = new QDialogButtonBox(XQDEUIIcon);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    hboxLayout4->addWidget(buttonBox);


    vboxLayout->addLayout(hboxLayout4);


    retranslateUi(XQDEUIIcon);
    QObject::connect(buttonBox, SIGNAL(accepted()), XQDEUIIcon, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), XQDEUIIcon, SLOT(reject()));

    tabWidget->setCurrentIndex(1);


    QMetaObject::connectSlotsByName(XQDEUIIcon);
    } // setupUi

    void retranslateUi(QDialog *XQDEUIIcon)
    {
    XQDEUIIcon->setWindowTitle(QApplication::translate("XQDEUIIcon", "Dialog", 0, QApplication::UnicodeUTF8));
    skipFeature->setText(QApplication::translate("XQDEUIIcon", "Skip this icon: will not displayed in the dock", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("XQDEUIIcon", "Unique name", 0, QApplication::UnicodeUTF8));
    keepindock->setText(QApplication::translate("XQDEUIIcon", "Keep in dock", 0, QApplication::UnicodeUTF8));
    groupwindows->setText(QApplication::translate("XQDEUIIcon", "Group similar windows", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("XQDEUIIcon", "Info", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("XQDEUIIcon", "Default image", 0, QApplication::UnicodeUTF8));
    enablepreview->setText(QApplication::translate("XQDEUIIcon", "Enable preview", 0, QApplication::UnicodeUTF8));
    enableIconFromWindow->setText(QApplication::translate("XQDEUIIcon", "Load always Icon from window", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("XQDEUIIcon", "Images", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("XQDEUIIcon", "Left mouse click", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("XQDEUIIcon", "if not running starts", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("XQDEUIIcon", "Actions", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("XQDEUIIcon", "Sensors will match these strings", 0, QApplication::UnicodeUTF8));
    addsl->setText(QApplication::translate("XQDEUIIcon", "Add", 0, QApplication::UnicodeUTF8));
    delsl->setText(QApplication::translate("XQDEUIIcon", "Del", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("XQDEUIIcon", "Connections", 0, QApplication::UnicodeUTF8));
    bSaveAsTemplate->setText(QApplication::translate("XQDEUIIcon", "Save as template", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(XQDEUIIcon);
    } // retranslateUi

};

namespace Ui {
    class XQDEUIIcon: public Ui_XQDEUIIcon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XQDEUIICON_H
