/********************************************************************************
** Form generated from reading UI file 'searchgui.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHGUI_H
#define UI_SEARCHGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchGUI
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SearchGUI)
    {
        if (SearchGUI->objectName().isEmpty())
            SearchGUI->setObjectName(QStringLiteral("SearchGUI"));
        SearchGUI->resize(986, 585);
        centralWidget = new QWidget(SearchGUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SearchGUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SearchGUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 986, 20));
        SearchGUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SearchGUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SearchGUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SearchGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SearchGUI->setStatusBar(statusBar);

        retranslateUi(SearchGUI);

        QMetaObject::connectSlotsByName(SearchGUI);
    } // setupUi

    void retranslateUi(QMainWindow *SearchGUI)
    {
        SearchGUI->setWindowTitle(QApplication::translate("SearchGUI", "SearchGUI", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchGUI: public Ui_SearchGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHGUI_H
