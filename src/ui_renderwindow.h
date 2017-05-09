/********************************************************************************
** Form generated from reading UI file 'renderwindowp10516.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RENDERWINDOWP10516_H
#define RENDERWINDOWP10516_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderWindow
{
public:
    QWidget *centralwidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_workMode;
    QPushButton *pushButton_viewMode;
    QPushButton *pushButton_resetView;

    void setupUi(QMainWindow *RenderWindow)
    {
        if (RenderWindow->objectName().isEmpty())
            RenderWindow->setObjectName(QStringLiteral("RenderWindow"));
        RenderWindow->resize(1000, 833);
        centralwidget = new QWidget(RenderWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 1000, 800));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 998, 798));
        scrollArea->setWidget(scrollAreaWidgetContents);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 800, 981, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_workMode = new QPushButton(horizontalLayoutWidget);
        pushButton_workMode->setObjectName(QStringLiteral("pushButton_workMode"));

        horizontalLayout->addWidget(pushButton_workMode);

        pushButton_viewMode = new QPushButton(horizontalLayoutWidget);
        pushButton_viewMode->setObjectName(QStringLiteral("pushButton_viewMode"));

        horizontalLayout->addWidget(pushButton_viewMode);

        pushButton_resetView = new QPushButton(horizontalLayoutWidget);
        pushButton_resetView->setObjectName(QStringLiteral("pushButton_resetView"));

        horizontalLayout->addWidget(pushButton_resetView);

        RenderWindow->setCentralWidget(centralwidget);

        retranslateUi(RenderWindow);

        QMetaObject::connectSlotsByName(RenderWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RenderWindow)
    {
        RenderWindow->setWindowTitle(QApplication::translate("RenderWindow", "MainWindow", Q_NULLPTR));
        pushButton_workMode->setText(QApplication::translate("RenderWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", Q_NULLPTR));
        pushButton_viewMode->setText(QApplication::translate("RenderWindow", "\350\247\206\345\233\276\346\250\241\345\274\217", Q_NULLPTR));
        pushButton_resetView->setText(QApplication::translate("RenderWindow", "\351\207\215\347\275\256\350\247\206\347\202\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RenderWindow: public Ui_RenderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RENDERWINDOWP10516_H
