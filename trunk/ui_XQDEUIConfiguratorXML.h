/********************************************************************************
** Form generated from reading ui file 'XQDEUIConfiguratorXML.ui'
**
** Created: Fri Feb 27 23:48:04 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_XQDEUICONFIGURATORXML_H
#define UI_XQDEUICONFIGURATORXML_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XQDEUIConfiguratorXML
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QListWidget *list_names;
    QTextEdit *var_description;
    QLabel *label_2;
    QLineEdit *var_value;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout2;
    QGridLayout *gridLayout1;
    QLabel *label_4;
    QLineEdit *c_name;
    QLabel *label_5;
    QLineEdit *c_author;
    QLabel *label_6;
    QLineEdit *c_ver;
    QLabel *label_7;
    QLineEdit *c_email;
    QLabel *label_8;
    QLineEdit *c_web;
    QLabel *label_9;
    QLineEdit *c_autoupdate;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *pOK;

    void setupUi(QDialog *XQDEUIConfiguratorXML)
    {
    if (XQDEUIConfiguratorXML->objectName().isEmpty())
        XQDEUIConfiguratorXML->setObjectName(QString::fromUtf8("XQDEUIConfiguratorXML"));
    XQDEUIConfiguratorXML->resize(368, 329);
    vboxLayout = new QVBoxLayout(XQDEUIConfiguratorXML);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    tabWidget = new QTabWidget(XQDEUIConfiguratorXML);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    vboxLayout1 = new QVBoxLayout(tab);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(tab);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    label_3 = new QLabel(tab);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 0, 1, 1, 1);

    list_names = new QListWidget(tab);
    list_names->setObjectName(QString::fromUtf8("list_names"));

    gridLayout->addWidget(list_names, 1, 0, 1, 1);

    var_description = new QTextEdit(tab);
    var_description->setObjectName(QString::fromUtf8("var_description"));

    gridLayout->addWidget(var_description, 1, 1, 1, 1);


    vboxLayout1->addLayout(gridLayout);

    label_2 = new QLabel(tab);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    vboxLayout1->addWidget(label_2);

    var_value = new QLineEdit(tab);
    var_value->setObjectName(QString::fromUtf8("var_value"));

    vboxLayout1->addWidget(var_value);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    vboxLayout2 = new QVBoxLayout(tab_2);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    gridLayout1 = new QGridLayout();
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    label_4 = new QLabel(tab_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout1->addWidget(label_4, 0, 0, 1, 1);

    c_name = new QLineEdit(tab_2);
    c_name->setObjectName(QString::fromUtf8("c_name"));

    gridLayout1->addWidget(c_name, 0, 1, 1, 1);

    label_5 = new QLabel(tab_2);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout1->addWidget(label_5, 1, 0, 1, 1);

    c_author = new QLineEdit(tab_2);
    c_author->setObjectName(QString::fromUtf8("c_author"));

    gridLayout1->addWidget(c_author, 1, 1, 1, 1);

    label_6 = new QLabel(tab_2);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout1->addWidget(label_6, 2, 0, 1, 1);

    c_ver = new QLineEdit(tab_2);
    c_ver->setObjectName(QString::fromUtf8("c_ver"));

    gridLayout1->addWidget(c_ver, 2, 1, 1, 1);

    label_7 = new QLabel(tab_2);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout1->addWidget(label_7, 3, 0, 1, 1);

    c_email = new QLineEdit(tab_2);
    c_email->setObjectName(QString::fromUtf8("c_email"));

    gridLayout1->addWidget(c_email, 3, 1, 1, 1);

    label_8 = new QLabel(tab_2);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout1->addWidget(label_8, 4, 0, 1, 1);

    c_web = new QLineEdit(tab_2);
    c_web->setObjectName(QString::fromUtf8("c_web"));

    gridLayout1->addWidget(c_web, 4, 1, 1, 1);

    label_9 = new QLabel(tab_2);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    gridLayout1->addWidget(label_9, 5, 0, 1, 1);

    c_autoupdate = new QLineEdit(tab_2);
    c_autoupdate->setObjectName(QString::fromUtf8("c_autoupdate"));

    gridLayout1->addWidget(c_autoupdate, 5, 1, 1, 1);


    vboxLayout2->addLayout(gridLayout1);

    tabWidget->addTab(tab_2, QString());

    vboxLayout->addWidget(tabWidget);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    pOK = new QPushButton(XQDEUIConfiguratorXML);
    pOK->setObjectName(QString::fromUtf8("pOK"));

    hboxLayout->addWidget(pOK);


    vboxLayout->addLayout(hboxLayout);


    retranslateUi(XQDEUIConfiguratorXML);

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(XQDEUIConfiguratorXML);
    } // setupUi

    void retranslateUi(QDialog *XQDEUIConfiguratorXML)
    {
    XQDEUIConfiguratorXML->setWindowTitle(QApplication::translate("XQDEUIConfiguratorXML", "Dialog", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("XQDEUIConfiguratorXML", "Values Name", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("XQDEUIConfiguratorXML", "Description", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("XQDEUIConfiguratorXML", "Value Data", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("XQDEUIConfiguratorXML", "Setup", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("XQDEUIConfiguratorXML", "Name", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("XQDEUIConfiguratorXML", "Author", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("XQDEUIConfiguratorXML", "Version", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("XQDEUIConfiguratorXML", "eMail", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("XQDEUIConfiguratorXML", "Website", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("XQDEUIConfiguratorXML", "Autoupgrade url", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("XQDEUIConfiguratorXML", "About", 0, QApplication::UnicodeUTF8));
    pOK->setText(QApplication::translate("XQDEUIConfiguratorXML", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(XQDEUIConfiguratorXML);
    } // retranslateUi

};

namespace Ui {
    class XQDEUIConfiguratorXML: public Ui_XQDEUIConfiguratorXML {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XQDEUICONFIGURATORXML_H
