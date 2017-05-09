/********************************************************************************
** Form generated from reading UI file 'folderimgsp44780.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FOLDERIMGSP44780_H
#define FOLDERIMGSP44780_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FolderImgs
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FolderImgs)
    {
        if (FolderImgs->objectName().isEmpty())
            FolderImgs->setObjectName(QStringLiteral("FolderImgs"));
        FolderImgs->resize(297, 378);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FolderImgs->sizePolicy().hasHeightForWidth());
        FolderImgs->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(FolderImgs);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(14);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(FolderImgs);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        verticalLayout->setStretch(0, 6);

        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addWidget(groupBox);

        verticalLayout_3->setStretch(0, 8);

        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        buttonBox = new QDialogButtonBox(FolderImgs);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalLayout_4->setStretch(0, 7);
        verticalLayout_4->setStretch(1, 1);

        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(FolderImgs);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), FolderImgs, SLOT(returnMain(QAbstractButton*)));

        QMetaObject::connectSlotsByName(FolderImgs);
    } // setupUi

    void retranslateUi(QDialog *FolderImgs)
    {
        FolderImgs->setWindowTitle(QApplication::translate("FolderImgs", "Load Images from folder", 0));
        groupBox->setTitle(QApplication::translate("FolderImgs", "Image files", 0));
    } // retranslateUi

};

namespace Ui {
    class FolderImgs: public Ui_FolderImgs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FOLDERIMGSP44780_H
