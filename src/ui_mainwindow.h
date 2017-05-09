/********************************************************************************
** Form generated from reading UI file 'mainwindowp12456.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWP12456_H
#define MAINWINDOWP12456_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myImageView.h"
#include "imgGraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_calib;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    MyImageView *graphicsView;
    ImgGraphicsView *graphicsView_6;
    QGroupBox *groupBox_2;
	MyImageView *graphicsView_2;
    ImgGraphicsView *graphicsView_7;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_open;
    QPushButton *pushButton_open;
    QPushButton *pushButton_cam;
    QLabel *label;
    QSlider *horizontalSlider_ev;
    QGroupBox *groupBox_left;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBox_r1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_x1;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_rot1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_y1;
    QGroupBox *groupBox_right;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBox_r2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_x2;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_rot2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_y2;
    QGroupBox *groupBox_preview;
    QPushButton *pushButton_render;
    QPushButton *pushButton_mode;
    QGroupBox *groupBox_stitch;
    QPushButton *pushButton_autoStitch;
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_36;
    QDoubleSpinBox *doubleSpinBox_cropRatio;
    QWidget *layoutWidget_10;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_38;
    QDoubleSpinBox *doubleSpinBox_roi_h;
    QWidget *layoutWidget_11;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_39;
    QDoubleSpinBox *doubleSpinBox_roi_w;
    QWidget *layoutWidget_12;
    QHBoxLayout *horizontalLayout_46;
    QLabel *label_40;
    QSpinBox *spinBox_conerRange;
    QWidget *layoutWidget_13;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_41;
    QDoubleSpinBox *doubleSpinBox_workScale;
    QWidget *layoutWidget_14;
    QHBoxLayout *horizontalLayout_48;
    QLabel *label_42;
    QDoubleSpinBox *doubleSpinBox_seamScale;
    QPushButton *pushButton_showDebug;
    QGroupBox *groupBox_save;
    QPushButton *pushButton_upload;
    QPushButton *pushButton_load;
    QPushButton *pushButton_save;
    QWidget *tab_test;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_4;
	MyImageView *graphicsView_app;
    QGroupBox *groupBox_3;
	MyImageView *graphicsView_cloud;
    QLabel *label_App;
    QPushButton *pushButton_testOnline;
    QLabel *label_Cloud;
    QLabel *label_Test;
    QPushButton *pushButton_app_cloud_switch;
    QPushButton *pushButton_testOffline;
    QPushButton *pushButton_sd_clear;
    QPushButton *pushButton_get_power;
    QPushButton *pushButton_get_sd_volume;
    QWidget *tab_pano;
    QPushButton *pushButton_openPano;
	MyImageView *graphicsView_pano;
    QLabel *label_currentState;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1594, 1004);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1598, 986));
        tab_calib = new QWidget();
        tab_calib->setObjectName(QStringLiteral("tab_calib"));
        horizontalLayoutWidget_4 = new QWidget(tab_calib);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 0, 1591, 961));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(horizontalLayoutWidget_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
		graphicsView = new MyImageView(1,groupBox);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 630, 630));
        graphicsView_6 = new ImgGraphicsView(groupBox);
        graphicsView_6->setObjectName(QStringLiteral("graphicsView_6"));
        graphicsView_6->setGeometry(QRect(0, 642, 630, 315));

        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
		graphicsView_2 = new MyImageView(1,groupBox_2);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(3, 0, 630, 630));
		graphicsView_7 = new ImgGraphicsView(groupBox_2);
        graphicsView_7->setObjectName(QStringLiteral("graphicsView_7"));
        graphicsView_7->setGeometry(QRect(3, 642, 630, 315));

        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 80);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_open = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_open->setObjectName(QStringLiteral("groupBox_open"));
        pushButton_open = new QPushButton(groupBox_open);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(170, 23, 131, 41));
        pushButton_cam = new QPushButton(groupBox_open);
        pushButton_cam->setObjectName(QStringLiteral("pushButton_cam"));
        pushButton_cam->setGeometry(QRect(10, 23, 131, 41));
        label = new QLabel(groupBox_open);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 90, 31, 21));
        horizontalSlider_ev = new QSlider(groupBox_open);
        horizontalSlider_ev->setObjectName(QStringLiteral("horizontalSlider_ev"));
        horizontalSlider_ev->setGeometry(QRect(50, 90, 251, 22));
        horizontalSlider_ev->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(groupBox_open);

        groupBox_left = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_left->setObjectName(QStringLiteral("groupBox_left"));
        horizontalLayoutWidget_2 = new QWidget(groupBox_left);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(2, 20, 311, 111));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_18 = new QLabel(horizontalLayoutWidget_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        horizontalLayout_21->addWidget(label_18);

        doubleSpinBox_r1 = new QDoubleSpinBox(horizontalLayoutWidget_2);
        doubleSpinBox_r1->setObjectName(QStringLiteral("doubleSpinBox_r1"));

        horizontalLayout_21->addWidget(doubleSpinBox_r1);

        horizontalLayout_21->setStretch(0, 4);
        horizontalLayout_21->setStretch(1, 6);

        verticalLayout_3->addLayout(horizontalLayout_21);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_3);

        doubleSpinBox_x1 = new QDoubleSpinBox(horizontalLayoutWidget_2);
        doubleSpinBox_x1->setObjectName(QStringLiteral("doubleSpinBox_x1"));

        horizontalLayout_6->addWidget(doubleSpinBox_x1);

        horizontalLayout_6->setStretch(0, 4);
        horizontalLayout_6->setStretch(1, 6);

        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_5);

        doubleSpinBox_rot1 = new QDoubleSpinBox(horizontalLayoutWidget_2);
        doubleSpinBox_rot1->setObjectName(QStringLiteral("doubleSpinBox_rot1"));

        horizontalLayout_8->addWidget(doubleSpinBox_rot1);

        horizontalLayout_8->setStretch(0, 4);
        horizontalLayout_8->setStretch(1, 6);

        verticalLayout_9->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_4);

        doubleSpinBox_y1 = new QDoubleSpinBox(horizontalLayoutWidget_2);
        doubleSpinBox_y1->setObjectName(QStringLiteral("doubleSpinBox_y1"));

        horizontalLayout_7->addWidget(doubleSpinBox_y1);

        horizontalLayout_7->setStretch(0, 4);
        horizontalLayout_7->setStretch(1, 6);

        verticalLayout_9->addLayout(horizontalLayout_7);


        horizontalLayout_3->addLayout(verticalLayout_9);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_2->addWidget(groupBox_left);

        groupBox_right = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_right->setObjectName(QStringLiteral("groupBox_right"));
        horizontalLayoutWidget_3 = new QWidget(groupBox_right);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(2, 20, 311, 111));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_19 = new QLabel(horizontalLayoutWidget_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        horizontalLayout_22->addWidget(label_19);

        doubleSpinBox_r2 = new QDoubleSpinBox(horizontalLayoutWidget_3);
        doubleSpinBox_r2->setObjectName(QStringLiteral("doubleSpinBox_r2"));

        horizontalLayout_22->addWidget(doubleSpinBox_r2);

        horizontalLayout_22->setStretch(0, 4);
        horizontalLayout_22->setStretch(1, 6);

        verticalLayout_4->addLayout(horizontalLayout_22);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_6 = new QLabel(horizontalLayoutWidget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_6);

        doubleSpinBox_x2 = new QDoubleSpinBox(horizontalLayoutWidget_3);
        doubleSpinBox_x2->setObjectName(QStringLiteral("doubleSpinBox_x2"));

        horizontalLayout_9->addWidget(doubleSpinBox_x2);

        horizontalLayout_9->setStretch(0, 4);
        horizontalLayout_9->setStretch(1, 6);

        verticalLayout_4->addLayout(horizontalLayout_9);


        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_8 = new QLabel(horizontalLayoutWidget_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_8);

        doubleSpinBox_rot2 = new QDoubleSpinBox(horizontalLayoutWidget_3);
        doubleSpinBox_rot2->setObjectName(QStringLiteral("doubleSpinBox_rot2"));

        horizontalLayout_11->addWidget(doubleSpinBox_rot2);

        horizontalLayout_11->setStretch(0, 4);
        horizontalLayout_11->setStretch(1, 6);

        verticalLayout_11->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_7 = new QLabel(horizontalLayoutWidget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label_7);

        doubleSpinBox_y2 = new QDoubleSpinBox(horizontalLayoutWidget_3);
        doubleSpinBox_y2->setObjectName(QStringLiteral("doubleSpinBox_y2"));

        horizontalLayout_10->addWidget(doubleSpinBox_y2);

        horizontalLayout_10->setStretch(0, 4);
        horizontalLayout_10->setStretch(1, 6);

        verticalLayout_11->addLayout(horizontalLayout_10);


        horizontalLayout_5->addLayout(verticalLayout_11);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_2->addWidget(groupBox_right);

        groupBox_preview = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_preview->setObjectName(QStringLiteral("groupBox_preview"));
        pushButton_render = new QPushButton(groupBox_preview);
        pushButton_render->setObjectName(QStringLiteral("pushButton_render"));
        pushButton_render->setGeometry(QRect(10, 30, 161, 81));
        pushButton_render->setAutoFillBackground(false);
        pushButton_mode = new QPushButton(groupBox_preview);
        pushButton_mode->setObjectName(QStringLiteral("pushButton_mode"));
        pushButton_mode->setGeometry(QRect(200, 30, 101, 81));

        verticalLayout_2->addWidget(groupBox_preview);

        groupBox_stitch = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_stitch->setObjectName(QStringLiteral("groupBox_stitch"));
        pushButton_autoStitch = new QPushButton(groupBox_stitch);
        pushButton_autoStitch->setObjectName(QStringLiteral("pushButton_autoStitch"));
        pushButton_autoStitch->setGeometry(QRect(10, 176, 161, 81));
        layoutWidget_9 = new QWidget(groupBox_stitch);
        layoutWidget_9->setObjectName(QStringLiteral("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(10, 80, 141, 31));
        horizontalLayout_39 = new QHBoxLayout(layoutWidget_9);
        horizontalLayout_39->setSpacing(0);
        horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
        horizontalLayout_39->setContentsMargins(0, 0, 0, 0);
        label_36 = new QLabel(layoutWidget_9);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setAlignment(Qt::AlignCenter);

        horizontalLayout_39->addWidget(label_36);

        doubleSpinBox_cropRatio = new QDoubleSpinBox(layoutWidget_9);
        doubleSpinBox_cropRatio->setObjectName(QStringLiteral("doubleSpinBox_cropRatio"));

        horizontalLayout_39->addWidget(doubleSpinBox_cropRatio);

        horizontalLayout_39->setStretch(0, 4);
        horizontalLayout_39->setStretch(1, 6);
        layoutWidget_10 = new QWidget(groupBox_stitch);
        layoutWidget_10->setObjectName(QStringLiteral("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(160, 80, 144, 31));
        horizontalLayout_44 = new QHBoxLayout(layoutWidget_10);
        horizontalLayout_44->setSpacing(0);
        horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));
        horizontalLayout_44->setContentsMargins(0, 0, 0, 0);
        label_38 = new QLabel(layoutWidget_10);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setAlignment(Qt::AlignCenter);

        horizontalLayout_44->addWidget(label_38);

        doubleSpinBox_roi_h = new QDoubleSpinBox(layoutWidget_10);
        doubleSpinBox_roi_h->setObjectName(QStringLiteral("doubleSpinBox_roi_h"));

        horizontalLayout_44->addWidget(doubleSpinBox_roi_h);

        horizontalLayout_44->setStretch(0, 4);
        horizontalLayout_44->setStretch(1, 6);
        layoutWidget_11 = new QWidget(groupBox_stitch);
        layoutWidget_11->setObjectName(QStringLiteral("layoutWidget_11"));
        layoutWidget_11->setGeometry(QRect(160, 30, 144, 31));
        horizontalLayout_45 = new QHBoxLayout(layoutWidget_11);
        horizontalLayout_45->setSpacing(0);
        horizontalLayout_45->setObjectName(QStringLiteral("horizontalLayout_45"));
        horizontalLayout_45->setContentsMargins(0, 0, 0, 0);
        label_39 = new QLabel(layoutWidget_11);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setAlignment(Qt::AlignCenter);

        horizontalLayout_45->addWidget(label_39);

        doubleSpinBox_roi_w = new QDoubleSpinBox(layoutWidget_11);
        doubleSpinBox_roi_w->setObjectName(QStringLiteral("doubleSpinBox_roi_w"));

        horizontalLayout_45->addWidget(doubleSpinBox_roi_w);

        horizontalLayout_45->setStretch(0, 4);
        horizontalLayout_45->setStretch(1, 6);
        layoutWidget_12 = new QWidget(groupBox_stitch);
        layoutWidget_12->setObjectName(QStringLiteral("layoutWidget_12"));
        layoutWidget_12->setGeometry(QRect(10, 30, 141, 31));
        horizontalLayout_46 = new QHBoxLayout(layoutWidget_12);
        horizontalLayout_46->setSpacing(0);
        horizontalLayout_46->setObjectName(QStringLiteral("horizontalLayout_46"));
        horizontalLayout_46->setContentsMargins(0, 0, 0, 0);
        label_40 = new QLabel(layoutWidget_12);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setAlignment(Qt::AlignCenter);

        horizontalLayout_46->addWidget(label_40);

        spinBox_conerRange = new QSpinBox(layoutWidget_12);
        spinBox_conerRange->setObjectName(QStringLiteral("spinBox_conerRange"));

        horizontalLayout_46->addWidget(spinBox_conerRange);

        horizontalLayout_46->setStretch(0, 4);
        horizontalLayout_46->setStretch(1, 6);
        layoutWidget_13 = new QWidget(groupBox_stitch);
        layoutWidget_13->setObjectName(QStringLiteral("layoutWidget_13"));
        layoutWidget_13->setGeometry(QRect(10, 130, 144, 31));
        horizontalLayout_47 = new QHBoxLayout(layoutWidget_13);
        horizontalLayout_47->setSpacing(0);
        horizontalLayout_47->setObjectName(QStringLiteral("horizontalLayout_47"));
        horizontalLayout_47->setContentsMargins(0, 0, 0, 0);
        label_41 = new QLabel(layoutWidget_13);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setAlignment(Qt::AlignCenter);

        horizontalLayout_47->addWidget(label_41);

        doubleSpinBox_workScale = new QDoubleSpinBox(layoutWidget_13);
        doubleSpinBox_workScale->setObjectName(QStringLiteral("doubleSpinBox_workScale"));

        horizontalLayout_47->addWidget(doubleSpinBox_workScale);

        horizontalLayout_47->setStretch(0, 5);
        horizontalLayout_47->setStretch(1, 5);
        layoutWidget_14 = new QWidget(groupBox_stitch);
        layoutWidget_14->setObjectName(QStringLiteral("layoutWidget_14"));
        layoutWidget_14->setGeometry(QRect(160, 130, 144, 31));
        horizontalLayout_48 = new QHBoxLayout(layoutWidget_14);
        horizontalLayout_48->setSpacing(0);
        horizontalLayout_48->setObjectName(QStringLiteral("horizontalLayout_48"));
        horizontalLayout_48->setContentsMargins(0, 0, 0, 0);
        label_42 = new QLabel(layoutWidget_14);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setAlignment(Qt::AlignCenter);

        horizontalLayout_48->addWidget(label_42);

        doubleSpinBox_seamScale = new QDoubleSpinBox(layoutWidget_14);
        doubleSpinBox_seamScale->setObjectName(QStringLiteral("doubleSpinBox_seamScale"));

        horizontalLayout_48->addWidget(doubleSpinBox_seamScale);

        horizontalLayout_48->setStretch(0, 5);
        horizontalLayout_48->setStretch(1, 5);
        pushButton_showDebug = new QPushButton(groupBox_stitch);
        pushButton_showDebug->setObjectName(QStringLiteral("pushButton_showDebug"));
        pushButton_showDebug->setGeometry(QRect(200, 176, 101, 81));

        verticalLayout_2->addWidget(groupBox_stitch);

        groupBox_save = new QGroupBox(horizontalLayoutWidget_4);
        groupBox_save->setObjectName(QStringLiteral("groupBox_save"));
        pushButton_upload = new QPushButton(groupBox_save);
        pushButton_upload->setObjectName(QStringLiteral("pushButton_upload"));
        pushButton_upload->setGeometry(QRect(170, 80, 131, 41));
        pushButton_load = new QPushButton(groupBox_save);
        pushButton_load->setObjectName(QStringLiteral("pushButton_load"));
        pushButton_load->setGeometry(QRect(170, 20, 131, 41));
        pushButton_save = new QPushButton(groupBox_save);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(10, 20, 131, 101));

        verticalLayout_2->addWidget(groupBox_save);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 2);
        verticalLayout_2->setStretch(2, 2);
        verticalLayout_2->setStretch(3, 2);
        verticalLayout_2->setStretch(4, 4);
        verticalLayout_2->setStretch(5, 2);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 80);
        horizontalLayout->setStretch(1, 20);
        tabWidget->addTab(tab_calib, QString());
        tab_test = new QWidget();
        tab_test->setObjectName(QStringLiteral("tab_test"));
        horizontalLayoutWidget = new QWidget(tab_test);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 20, 1591, 811));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(horizontalLayoutWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
		graphicsView_app = new MyImageView(0,groupBox_4);
        graphicsView_app->setObjectName(QStringLiteral("graphicsView_app"));
        graphicsView_app->setGeometry(QRect(0, 13, 791, 791));

        horizontalLayout_4->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(horizontalLayoutWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
		graphicsView_cloud = new MyImageView(0, groupBox_3);
        graphicsView_cloud->setObjectName(QStringLiteral("graphicsView_cloud"));
        graphicsView_cloud->setGeometry(QRect(0, 13, 791, 791));

        horizontalLayout_4->addWidget(groupBox_3);

        label_App = new QLabel(tab_test);
        label_App->setObjectName(QStringLiteral("label_App"));
        label_App->setGeometry(QRect(10, 834, 501, 21));
        pushButton_testOnline = new QPushButton(tab_test);
        pushButton_testOnline->setObjectName(QStringLiteral("pushButton_testOnline"));
        pushButton_testOnline->setGeometry(QRect(150, 860, 111, 101));
        label_Cloud = new QLabel(tab_test);
        label_Cloud->setObjectName(QStringLiteral("label_Cloud"));
        label_Cloud->setGeometry(QRect(1080, 834, 491, 20));
        label_Test = new QLabel(tab_test);
        label_Test->setObjectName(QStringLiteral("label_Test"));
        label_Test->setGeometry(QRect(520, 834, 551, 20));
        pushButton_app_cloud_switch = new QPushButton(tab_test);
        pushButton_app_cloud_switch->setObjectName(QStringLiteral("pushButton_app_cloud_switch"));
        pushButton_app_cloud_switch->setGeometry(QRect(710, 860, 170, 101));
        pushButton_testOffline = new QPushButton(tab_test);
        pushButton_testOffline->setObjectName(QStringLiteral("pushButton_testOffline"));
        pushButton_testOffline->setGeometry(QRect(1330, 860, 111, 101));
        pushButton_sd_clear = new QPushButton(tab_test);
        pushButton_sd_clear->setObjectName(QStringLiteral("pushButton_sd_clear"));
        pushButton_sd_clear->setGeometry(QRect(1470, 860, 111, 101));
        pushButton_get_power = new QPushButton(tab_test);
        pushButton_get_power->setObjectName(QStringLiteral("pushButton_get_power"));
        pushButton_get_power->setGeometry(QRect(10, 860, 111, 51));
        pushButton_get_sd_volume = new QPushButton(tab_test);
        pushButton_get_sd_volume->setObjectName(QStringLiteral("pushButton_get_sd_volume"));
        pushButton_get_sd_volume->setGeometry(QRect(10, 910, 111, 51));
        tabWidget->addTab(tab_test, QString());
        tab_pano = new QWidget();
        tab_pano->setObjectName(QStringLiteral("tab_pano"));
        pushButton_openPano = new QPushButton(tab_pano);
        pushButton_openPano->setObjectName(QStringLiteral("pushButton_openPano"));
        pushButton_openPano->setGeometry(QRect(1350, 840, 221, 51));
		graphicsView_pano = new MyImageView(0, tab_pano);
        graphicsView_pano->setObjectName(QStringLiteral("graphicsView_pano"));
        graphicsView_pano->setGeometry(QRect(5, 7, 1580, 790));
        tabWidget->addTab(tab_pano, QString());
        label_currentState = new QLabel(centralwidget);
        label_currentState->setObjectName(QStringLiteral("label_currentState"));
        label_currentState->setGeometry(QRect(6, 985, 1581, 16));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        groupBox_open->setTitle(QApplication::translate("MainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        pushButton_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_cam->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\233\235\345\205\211", Q_NULLPTR));
        groupBox_left->setTitle(QApplication::translate("MainWindow", "\345\267\246\345\233\276\357\274\210\345\210\235\347\272\247\345\217\202\346\225\260\357\274\211", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "\345\215\212\345\276\204", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\234\206\345\277\203-X", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\234\206\345\277\203-Y", Q_NULLPTR));
        groupBox_right->setTitle(QApplication::translate("MainWindow", "\345\217\263\345\233\276\357\274\210\345\210\235\347\272\247\345\217\202\346\225\260\357\274\211", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "\345\215\212\345\276\204", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\234\206\345\277\203-X", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\345\234\206\345\277\203-Y", Q_NULLPTR));
        groupBox_preview->setTitle(QApplication::translate("MainWindow", "\351\242\204\350\247\210", Q_NULLPTR));
        pushButton_render->setText(QApplication::translate("MainWindow", "\346\270\262\346\237\223", Q_NULLPTR));
        pushButton_mode->setText(QApplication::translate("MainWindow", "\345\256\236\346\227\266\351\242\204\350\247\210/\351\235\236\345\256\236\346\227\266", Q_NULLPTR));
        groupBox_stitch->setTitle(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\213\274\346\216\245\357\274\210\351\253\230\347\272\247\345\217\202\346\225\260\357\274\214\350\257\267\345\213\277\351\232\217\344\276\277\346\233\264\346\224\271\357\274\211", Q_NULLPTR));
        pushButton_autoStitch->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\213\274\346\216\245", Q_NULLPTR));
        label_36->setText(QApplication::translate("MainWindow", "\346\213\274\346\216\245\350\243\201\345\211\252\346\257\224\344\276\213", Q_NULLPTR));
        label_38->setText(QApplication::translate("MainWindow", "\347\253\226\347\233\264\350\214\203\345\233\264\357\274\210\345\244\226\357\274\211", Q_NULLPTR));
        label_39->setText(QApplication::translate("MainWindow", "\346\260\264\345\271\263\350\214\203\345\233\264\357\274\210\345\206\205\357\274\211", Q_NULLPTR));
        label_40->setText(QApplication::translate("MainWindow", "\350\247\222\347\202\271\345\257\273\346\211\276\350\214\203\345\233\264", Q_NULLPTR));
        label_41->setText(QApplication::translate("MainWindow", "\346\213\274\346\216\245\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        label_42->setText(QApplication::translate("MainWindow", "\350\236\215\345\220\210\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        pushButton_showDebug->setText(QApplication::translate("MainWindow", "\350\260\203\350\257\225\345\233\276\345\203\217ON/OFF", Q_NULLPTR));
        groupBox_save->setTitle(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_upload->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_load->setText(QApplication::translate("MainWindow", "\350\275\275\345\205\245", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_calib), QApplication::translate("MainWindow", "\345\217\214\347\233\256\351\261\274\347\234\274\346\240\207\345\256\232", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\346\211\213\346\234\272\347\253\257\346\225\210\346\236\234", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\344\272\221\347\253\257\346\225\210\346\236\234", Q_NULLPTR));
        label_App->setText(QString());
        pushButton_testOnline->setText(QApplication::translate("MainWindow", "\345\234\250\347\272\277\346\265\213\350\257\225", Q_NULLPTR));
        label_Cloud->setText(QString());
        label_Test->setText(QString());
        pushButton_app_cloud_switch->setText(QApplication::translate("MainWindow", "\344\272\221\347\253\257/\346\211\213\346\234\272\347\253\257\346\270\262\346\237\223\345\210\207\346\215\242", Q_NULLPTR));
        pushButton_testOffline->setText(QApplication::translate("MainWindow", "\347\246\273\347\272\277\346\265\213\350\257\225", Q_NULLPTR));
        pushButton_sd_clear->setText(QApplication::translate("MainWindow", "\345\207\272\345\216\202\345\211\215\346\270\205\351\231\244SD\345\215\241", Q_NULLPTR));
        pushButton_get_power->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\347\233\270\346\234\272\347\224\265\351\207\217", Q_NULLPTR));
        pushButton_get_sd_volume->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\347\233\270\346\234\272SD\345\215\241\345\256\271\351\207\217", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_test), QApplication::translate("MainWindow", "    \346\265\213\350\257\225    ", Q_NULLPTR));
        pushButton_openPano->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\260\345\205\250\346\231\257\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_pano), QApplication::translate("MainWindow", " \345\205\250\346\231\257\345\233\276\346\237\245\347\234\213 ", Q_NULLPTR));
        label_currentState->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWP12456_H
