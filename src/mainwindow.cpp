#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setFixedSize(this->width(), this->height());

	lang = chinese;
	
	ui->doubleSpinBox_x1->setRange(0, 8000); ui->doubleSpinBox_y1->setRange(0, 8000); 
	ui->doubleSpinBox_x2->setRange(0, 8000); ui->doubleSpinBox_y2->setRange(0, 8000); 
	
	ui->doubleSpinBox_rot1->setRange(-180, 180); ui->doubleSpinBox_rot1->setSingleStep(0.1);
	ui->doubleSpinBox_rot2->setRange(-180, 180); ui->doubleSpinBox_rot2->setSingleStep(0.1);

	ui->doubleSpinBox_r1->setRange(5, 8000); 
	ui->doubleSpinBox_r2->setRange(5, 8000); 
	
	connect(ui->graphicsView, SIGNAL(circleResized(double)), this, SLOT(on_imgRadiusChanged(double)));
	connect(ui->graphicsView_2, SIGNAL(circleResized(double)), this, SLOT(on_imgRadiusChanged(double)));
	
	connect(ui->graphicsView, SIGNAL(circleMoved(QPointF)), this, SLOT(on_imgMoved(QPointF)));
	connect(ui->graphicsView_2, SIGNAL(circleMoved(QPointF)), this, SLOT(on_imgMoved(QPointF)));
	
	connect(ui->doubleSpinBox_x1, SIGNAL(valueChanged(double)), ui->graphicsView, SLOT(setItemPosX(double)));
	connect(ui->doubleSpinBox_y1, SIGNAL(valueChanged(double)), ui->graphicsView, SLOT(setItemPosY(double)));
	connect(ui->doubleSpinBox_r1, SIGNAL(valueChanged(double)), ui->graphicsView, SLOT(setItemSize(double)));

	connect(ui->doubleSpinBox_x2, SIGNAL(valueChanged(double)), ui->graphicsView_2, SLOT(setItemPosX(double)));
	connect(ui->doubleSpinBox_y2, SIGNAL(valueChanged(double)), ui->graphicsView_2, SLOT(setItemPosY(double)));
	connect(ui->doubleSpinBox_r2, SIGNAL(valueChanged(double)), ui->graphicsView_2, SLOT(setItemSize(double)));

	//------------------------------------------------------------------------------------------------------------

	connect(ui->graphicsView_6, SIGNAL(mouseMoved(QPointF)), this, SLOT(on_imgMoved(QPointF)));
	connect(ui->graphicsView_7, SIGNAL(mouseMoved(QPointF)), this, SLOT(on_imgMoved(QPointF)));
	
	connect(ui->graphicsView_6, SIGNAL(mouseRotate(double)), this, SLOT(on_imgRotated(double)));
	connect(ui->graphicsView_7, SIGNAL(mouseRotate(double)), this, SLOT(on_imgRotated(double)));
	
	connect(ui->doubleSpinBox_rot1, SIGNAL(valueChanged(double)), ui->graphicsView_6, SLOT(on_AccAngle_changed(double)));	
	connect(ui->doubleSpinBox_x1, SIGNAL(valueChanged(double)), ui->graphicsView_6, SLOT(on_AccPosX_changed(double)));
	connect(ui->doubleSpinBox_y1, SIGNAL(valueChanged(double)), ui->graphicsView_6, SLOT(on_AccPosY_changed(double)));

	connect(ui->doubleSpinBox_rot2, SIGNAL(valueChanged(double)), ui->graphicsView_7, SLOT(on_AccAngle_changed(double)));
	connect(ui->doubleSpinBox_x2, SIGNAL(valueChanged(double)), ui->graphicsView_7, SLOT(on_AccPosX_changed(double)));
	connect(ui->doubleSpinBox_y2, SIGNAL(valueChanged(double)), ui->graphicsView_7, SLOT(on_AccPosY_changed(double)));


	//----------------------------��ʼ״̬����----------------------------
	ui->groupBox_left->setDisabled(true);
	ui->groupBox_right->setDisabled(true);
	ui->groupBox_preview->setDisabled(true);
	ui->groupBox_stitch->setDisabled(true);
	ui->groupBox_save->setDisabled(true);

	ui->pushButton_testOnline->setDisabled(true);
	ui->pushButton_app_cloud_switch->setDisabled(true);

	//�������ⰴ����ɫ
	QPalette   pal;
	pal.setColor(QPalette::ButtonText, QColor(200, 200, 200));

	ui->pushButton_open->setPalette(pal);
	ui->pushButton_open->setStyleSheet("background-color: rgb(55, 55, 55);");
	ui->pushButton_mode->setPalette(pal);
	ui->pushButton_mode->setStyleSheet("background-color: rgb(155, 155, 155);");

	ui->pushButton_render->setPalette(pal);
	ui->pushButton_render->setStyleSheet("background-color: rgb(155, 155, 155);");
	ui->pushButton_load->setPalette(pal);
	ui->pushButton_load->setStyleSheet("background-color: rgb(155, 155, 155);");	

	ui->pushButton_autoStitch->setPalette(pal);
	ui->pushButton_autoStitch->setStyleSheet("background-color: rgb(155, 155, 155);");

	ui->pushButton_showDebug->setPalette(pal);
	ui->pushButton_showDebug->setStyleSheet("background-color: rgb(155, 155, 155);");

	_renderWindow = new RenderWindow(this);
	_renderWindow->setWindowTitle(QString::fromLocal8Bit("��ȾԤ��"));

	connect(_renderWindow, SIGNAL(panoImgChanged()), this, SLOT(on_renderImgChanged()));
	render_pano_changed = false;

	firstRun = true;
	_activ_idx = -1;
	isRTMode = true; //default mode: realtime mode
	app_cloud_switch = false;
	_showDebugImg = false;

	ui->doubleSpinBox_cropRatio->setSingleStep(0.01);
	ui->spinBox_conerRange->setRange(0, 1000);
	ui->spinBox_conerRange->setValue(300);
	ui->doubleSpinBox_seamScale->setRange(0.1, 1.0);
	ui->doubleSpinBox_seamScale->setValue(0.2);
	ui->doubleSpinBox_seamScale->setSingleStep(0.05);
	ui->doubleSpinBox_workScale->setRange(0.1, 1.0);
	ui->doubleSpinBox_workScale->setValue(1.0);
	ui->doubleSpinBox_workScale->setSingleStep(0.05);
	ui->doubleSpinBox_roi_h->setRange(0, 1);
	ui->doubleSpinBox_roi_h->setSingleStep(0.01);
	ui->doubleSpinBox_roi_w->setRange(0, 1);
	ui->doubleSpinBox_roi_w->setSingleStep(0.01);

	//��ʱ����
	ui->doubleSpinBox_seamScale->setDisabled(true);
	ui->doubleSpinBox_workScale->setDisabled(true);

	//�ع����������
	ui->horizontalSlider_ev->setTickInterval(1);
	ui->horizontalSlider_ev->setRange(0, 12);
	ui->horizontalSlider_ev->setValue(6);
	
	connect(ui->horizontalSlider_ev, SIGNAL(sliderReleased()), this, SLOT(on_sliderReleased()));


	_scale = (double)CALIB_SIZE / FULL_SIZE;
	
	//----------------------------------------�궨��Աʹ�ð汾��ֱ�Ӷ������úõľ�ͷ����-------------------------------------//
	QString path_str = "../param_v2";//"D:/ipanoAll/param_v2";// "../param_JSD1336";//
	
	QDir cpath(path_str);
	if (!cpath.exists())
	{
		_mkdir(path_str.toStdString().c_str());
	}
	
	commonParamPath = path_str.toStdString();

	readCommonParams();

	initMem();

	checkWlanStatus();

	//httpͨ��
	m_pNetworkManager = new QNetworkAccessManager(this);
	m_pNetworkReply = NULL;

// 	m_pTimer = new QTimer;
// 	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(requestTimeout()));//��ʱ�ź�
}


MainWindow::~MainWindow()
{
	delete ui;
	delete _renderWindow;
}

//��ʼ���ڴ��ӳ���
void MainWindow::initMem()
{
	for (int i = 0; i < IMG_NUM; ++i)
	{	
		correctImg[i] = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, IMG_FORMAT);
		maskImg[i] = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, IMG_FORMAT);
		stitchImg[i] = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, IMG_FORMAT);
		stitchImg_2[i] = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, IMG_FORMAT);
		smapX[i] = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, CV_32FC1);
		smapY[i] = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, CV_32FC1);
	}

	mapX = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, CV_32FC1);
	mapY = Mat::zeros(CALIB_SIZE, CALIB_SIZE * 2, CV_32FC1);
	HDmapX = Mat::zeros(FULL_SIZE, FULL_SIZE * 2, CV_32FC1);
	HDmapY = Mat::zeros(FULL_SIZE, FULL_SIZE * 2, CV_32FC1);

	readMaps();
	readMasks();
	readHDMaps();
}


void MainWindow::checkWlanStatus()
{
	QNetworkConfiguration cfg;
	QNetworkConfigurationManager ncm;
	ncm.updateConfigurations();

	auto nc = ncm.allConfigurations();

	int w_cnt = 0;
	vector<QNetworkConfiguration> valid_wifi_list;

	for (auto &x : nc)
	{
		if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
		{		
			if (x.name().contains("NVT_CARDV") || x.name().contains("HFT") || x.name().contains("IPANO"))
			{
				valid_wifi_list.push_back(x);
				cout << "available camera wlan #" << QString::number(++w_cnt).toStdString() << ": " << x.name().toStdString() << endl;
			}
		}
	}

	if (valid_wifi_list.size()>0)
	{
		cfg = valid_wifi_list[0];//Ĭ������һ����������wifi
		_wlanName = cfg.name();
	}
	else
	{
		if (lang == english)
		{
			ui->label_currentState->setText("valid wifi not found, please check if the camera wifi is opened!");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�Ҳ�����Ч�����wifi����ȷ�����wifi�Ѵ򿪣�"));
		}
		return;
	}

	auto session = new QNetworkSession(cfg, this);
	session->open(); //���Զ�����һ�����������wifi����һ������������wifi

	connect(session, SIGNAL(opened()), this, SLOT(wifiLinkResult()));

// 	if (session->configuration().state() == QNetworkSession::Connected)
// 	{
// 		cout << session->configuration().name().toStdString() << " is connected." << endl;
// 	}
}


void MainWindow::wifiLinkResult()
{
	cout << "wifi: "<<_wlanName.toStdString()<<" connected successful." << endl;
}


bool MainWindow::getConnectedWiFiName()
{
	QNetworkConfiguration cfg;
	QNetworkConfigurationManager ncm;
	ncm.updateConfigurations();

	auto nc = ncm.allConfigurations();

	int w_cnt = 0;
	vector<QNetworkConfiguration> valid_wifi_list;

	for (auto &x : nc)
	{
		if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
		{
			if (x.name().contains("NVT_CARDV") || x.name().contains("HFT") || x.name().contains("IPANO"))
			{
				auto session = new QNetworkSession(x, this);


			}
		}
	}

	return false;
}


void MainWindow::on_renderImgChanged()
{
	if ((!_panoPreview.empty()) && (!_panoStitch.empty()))
	{
		render_pano_changed = !render_pano_changed;
		if (render_pano_changed)
		{
			_renderWindow->updatePanoImg(_panoPreview);
			_renderWindow->setWindowTitle(QString::fromLocal8Bit("��ȾԤ��-Ӳƴ���"));
			_renderWindow->show();
		}
		else
		{
			_renderWindow->updatePanoImg(_panoStitch);
			_renderWindow->setWindowTitle(QString::fromLocal8Bit("��ȾԤ��-�ںϽ��"));
			_renderWindow->show();
		}
	}
}


void MainWindow::on_pushButton_app_cloud_switch_clicked()
{
	app_cloud_switch = !app_cloud_switch;

	if (app_cloud_switch)
	{
		_renderWindow->updatePanoImg(_panoApp);
		_renderWindow->setWindowTitle(QString::fromLocal8Bit("�ֻ�����Ⱦ���"));
		_renderWindow->show();
	}
	else
	{		
		_renderWindow->updatePanoImg(_panoCloud);
		_renderWindow->setWindowTitle(QString::fromLocal8Bit("�ƶ���Ⱦ���"));
		_renderWindow->show();
	}
}


void MainWindow::on_pushButton_testOnline_clicked()
{
	if (!captureImg(testPath, false))
	{
		if (lang == english)
		{
			ui->label_Test->setText("capture failed, please check and retry!");
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("����ʧ�ܣ���������ԣ�"));
		}

		return;
	}

	appTest();
	cloudTest();	

	_renderWindow->updatePanoImg(_panoCloud);
	_renderWindow->setWindowTitle(QString::fromLocal8Bit("�ƶ���Ⱦ���"));
	_renderWindow->show();

	ui->pushButton_app_cloud_switch->setEnabled(true);

}


void MainWindow::on_pushButton_testOffline_clicked()
{	
	if (testPath != "")
	{
		appTest();
		cloudTest();

		_renderWindow->updatePanoImg(_panoCloud);
		_renderWindow->setWindowTitle(QString::fromLocal8Bit("�ƶ���Ⱦ���"));
		_renderWindow->show();

		ui->pushButton_app_cloud_switch->setEnabled(true);
	}
	else
	{
		if (lang == english)
		{
			ui->label_Test->setText("please chose a directory first!");
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("��ָ�����߲����ļ�Ŀ¼�ȣ�"));
		}
	}
}


void MainWindow::appTest()
{
	int64 tic = getTickCount();

	StiProcess panoProcess(testPath.toStdString(), QProPath.toStdString(), commonParamPath, CALIB_SIZE, 0.5);
	panoProcess.setFusionArgs(0.25, 5, true);
	panoProcess.setStiMode(0);
	panoProcess.setStitchSize(CALIB_SIZE);
	panoProcess.setStitchScale(0.5);
	panoProcess.loadMaps(mapX, mapY);

	_panoApp = panoProcess.exec();

	ui->graphicsView_app->setPixmap(Mat2QImage(_panoApp));

	imwrite(testPath.toStdString() + "/panorama_app.jpg", _panoApp);

	if (lang == english)
	{
		ui->label_App->setText("app test accomplished, time elapsed: " + QString::number(double(getTickCount() - tic) / getTickFrequency()) + " s. ");
	}
	else
	{
		ui->label_App->setText(QString::fromLocal8Bit("�ֻ��˲�����ɣ���ʱ�� ") + QString::number(double(getTickCount() - tic) / getTickFrequency()) + " s. ");
	}
}


void MainWindow::cloudTest()
{
	int64 tic = getTickCount();

	StiProcess panoProcess(testPath.toStdString(), QProPath.toStdString(), commonParamPath, FULL_SIZE, 1.0);
	panoProcess.setFusionArgs(0.15, 5, true);
	panoProcess.setStiMode(1);
	panoProcess.setStitchSize(FULL_SIZE);
	panoProcess.setStitchScale(1.0);
	panoProcess.loadMaps(HDmapX, HDmapY);

	_panoCloud = panoProcess.exec();

	ui->graphicsView_cloud->setPixmap(Mat2QImage(_panoCloud));

	imwrite(testPath.toStdString() + "/panorama_cloud.jpg", _panoCloud);

	if (lang == english)
	{
		ui->label_Cloud->setText("cloud test accomplished, time elapsed: " + QString::number(double(getTickCount() - tic) / getTickFrequency()) + " s. ");
	}
	else
	{
		ui->label_Cloud->setText(QString::fromLocal8Bit("�ƶ˲�����ɣ���ʱ�� ") + QString::number(double(getTickCount() - tic) / getTickFrequency()) + " s. ");
	}
}


void MainWindow::on_pushButton_open_clicked()
{
	QProPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../data",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	testPath = QProPath + "/test";
	QDir tpath(testPath);
	if (!tpath.exists())
	{
		_mkdir(testPath.toStdString().c_str());
	}


	if (QProPath != "")
	{
		ui->label_Test->setText("");
		ui->label_App->setText("");
		ui->label_Cloud->setText("");

		this->setWindowTitle(QString::fromLocal8Bit("���ھ۴�IPANOȫ������궨��� - ") + QProPath);//.right(6)

		bool isLoaded = true;

		srcImg[0] = imread(QProPath.toStdString() + "/Image1.jpg");
		if (srcImg[0].empty())	isLoaded = false;
		
		srcImg[1] = imread(QProPath.toStdString() + "/Image2.jpg");
		if (srcImg[1].empty())	isLoaded = false;
		
		if (!isLoaded)
		{
			if (lang == english)
			{
				QMessageBox::information(this, "Error", "can not find enough images !");
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷��ҵ��㹻��ͼƬ!"));
			}			

			return;
		}
		else
		{
			firstRun = true;

			//ͼ����С���������ٱ궨����
			cv::resize(srcImg[0], scaleSrcImg[0], Size(), _scale, _scale);
			cv::resize(srcImg[1], scaleSrcImg[1], Size(), _scale, _scale);

			ui->graphicsView->setPixmap(Mat2QImage(srcImg[0]));
			ui->graphicsView_2->setPixmap(Mat2QImage(srcImg[1]));

			if (lang == english)
			{
				ui->label_currentState->setText("source images are loaded successful.");
			}
			else
			{
				ui->label_currentState->setText(QString::fromLocal8Bit("Դͼ������ɹ�."));
			}

			ui->groupBox_left->setEnabled(true);
			ui->groupBox_right->setEnabled(true);
			ui->groupBox_preview->setEnabled(true);
			ui->groupBox_save->setEnabled(true);

			ui->pushButton_load->setStyleSheet("background-color: rgb(55, 55, 55);");
			ui->pushButton_render->setStyleSheet("background-color: rgb(55, 55, 55);");
			ui->pushButton_mode->setStyleSheet("background-color: rgb(55, 55, 55);");
				
		}	
	}
}


void  MainWindow::on_pushButton_render_clicked()
{
	firstRun = false;

	QPointF center[IMG_NUM] = { QPointF(ui->doubleSpinBox_x1->value(), ui->doubleSpinBox_y1->value()),
		QPointF(ui->doubleSpinBox_x2->value(), ui->doubleSpinBox_y2->value())};

	double radius[IMG_NUM] = { ui->doubleSpinBox_r1->value(),
		ui->doubleSpinBox_r2->value()};

	double ang[IMG_NUM] = { ui->doubleSpinBox_rot1->value(),
		ui->doubleSpinBox_rot2->value()};

#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < IMG_NUM; ++i)
	{
		imgProcessFromMotion(center[i], radius[i], ang[i], i);
	}

	ui->graphicsView_6->setPixmap(Mat2QImage(correctImg[0]));
	ui->graphicsView_7->setPixmap(Mat2QImage(correctImg[1]));	

	composePano();

	ui->groupBox_stitch->setEnabled(true);
	ui->pushButton_autoStitch->setStyleSheet("background-color: rgb(55, 55, 55);");


	if (lang == english)
	{
		ui->label_currentState->setText("rendering finished.");
	}
	else
	{
		ui->label_currentState->setText(QString::fromLocal8Bit("��Ⱦ���."));
	}
}


void MainWindow::composePano()
{
	_panoPreview = stitchImg[0] + stitchImg[1];	

	showImg("ƴ��Ԥ��_��Ӱ���", _panoPreview, 900.f / (float)CALIB_SIZE);

	Mat panoPreview_2 = stitchImg_2[0] + stitchImg_2[1];
	showImg("ƴ��Ԥ��", panoPreview_2, 900.f / (float)CALIB_SIZE);

	_renderWindow->updatePanoImg(_panoPreview);
	_renderWindow->setWindowTitle(QString::fromLocal8Bit("��ȾԤ��-Ӳƴ���"));

	_renderWindow->show();

}


QImage MainWindow::Mat2QImage(InputArray srcimg)
{
	Mat src = srcimg.getMat();
	cv::Mat temp; // make the same cv::Mat  
	cvtColor(src, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need  
	QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	dest.bits(); // enforce deep copy, see documentation of QImage::QImage ( const uchar * data, int width, int height, Format format )  
	return dest;
}


void MainWindow::on_pushButton_mode_clicked()
{
	isRTMode = !isRTMode;
	if (isRTMode)
	{
		ui->pushButton_mode->setStyleSheet("background-color: rgb(55, 55, 55);");

		if (lang == english)
		{
			ui->label_currentState->setText("preView mode activated.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("ʵʱԤ��ģʽ����."));
		}
	}
	else
	{
		ui->pushButton_mode->setStyleSheet("background-color: rgb(155, 155, 155);");

		if (lang == english)
		{
			ui->label_currentState->setText("preView mode closed.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("ʵʱԤ��ģʽ�ر�."));
		}
	}

}


//-------------------ͼ������ص�����---------------------------
void MainWindow::on_imgRotated(double ang)
{
	if (isRTMode && !firstRun)
	{
		if (sender() == ui->graphicsView_6)
		{
			imgProcessFromMotion(QPointF(ui->doubleSpinBox_x1->value(), ui->doubleSpinBox_y1->value()), ui->doubleSpinBox_r1->value(), ang, 0);

			ui->doubleSpinBox_rot1->setValue(ang);
			ui->graphicsView_6->setPixmap(Mat2QImage(correctImg[0]));

			_activ_idx = 0;

			composePano();
		}
		else if (sender() == ui->graphicsView_7)
		{
			imgProcessFromMotion(QPointF(ui->doubleSpinBox_x2->value(), ui->doubleSpinBox_y2->value()), ui->doubleSpinBox_r2->value(), ang, 1);

			ui->doubleSpinBox_rot2->setValue(ang);
			ui->graphicsView_7->setPixmap(Mat2QImage(correctImg[1]));

			_activ_idx = 1;

			composePano();
		}				
	}
	else
	{
		if (sender() == ui->graphicsView_6)
		{
			ui->doubleSpinBox_rot1->setValue(ang);
			_activ_idx = 0;
		}
		else if (sender() == ui->graphicsView_7)
		{
			ui->doubleSpinBox_rot2->setValue(ang);
			_activ_idx = 1;
		}
		
	}
	
}


void MainWindow::on_imgMoved(QPointF p)
{
	if (isRTMode && !firstRun)
	{
		if (sender() == ui->graphicsView || sender() == ui->graphicsView_6)
		{
			imgProcessFromMotion(p, ui->doubleSpinBox_r1->value(), ui->doubleSpinBox_rot1->value(), 0);

			ui->doubleSpinBox_x1->setValue(p.x());
			ui->doubleSpinBox_y1->setValue(p.y());
			ui->graphicsView_6->setPixmap(Mat2QImage(correctImg[0]));

			_activ_idx = 0;

			composePano();
		}
		else if (sender() == ui->graphicsView_2 || sender() == ui->graphicsView_7)
		{
			imgProcessFromMotion(p, ui->doubleSpinBox_r2->value(), ui->doubleSpinBox_rot2->value(), 1);

			ui->doubleSpinBox_x2->setValue(p.x());
			ui->doubleSpinBox_y2->setValue(p.y());
			ui->graphicsView_7->setPixmap(Mat2QImage(correctImg[1]));

			_activ_idx = 1;

			composePano();
		}		
	}
	else
	{
		if (sender() == ui->graphicsView || sender() == ui->graphicsView_6)
		{
			ui->doubleSpinBox_x1->setValue(p.x());
			ui->doubleSpinBox_y1->setValue(p.y());
			_activ_idx = 0;
		}
		else if (sender() == ui->graphicsView_2 || sender() == ui->graphicsView_7)
		{
			ui->doubleSpinBox_x2->setValue(p.x());
			ui->doubleSpinBox_y2->setValue(p.y());
			_activ_idx = 1;
		}		
	}
	
}


void MainWindow::on_imgRadiusChanged(double arg)
{
	if (isRTMode && !firstRun)
	{
		if (sender() == ui->graphicsView)
		{
			imgProcessFromMotion(QPointF(ui->doubleSpinBox_x1->value(), ui->doubleSpinBox_y1->value()), arg, ui->doubleSpinBox_rot1->value(), 0);

			ui->doubleSpinBox_r1->setValue(arg);
			ui->graphicsView_6->setPixmap(Mat2QImage(correctImg[0]));
			_activ_idx = 0;

			composePano();
		}
		else if (sender() == ui->graphicsView_2)
		{
			imgProcessFromMotion(QPointF(ui->doubleSpinBox_x2->value(), ui->doubleSpinBox_y2->value()), arg, ui->doubleSpinBox_rot2->value(), 1);

			ui->doubleSpinBox_r2->setValue(arg);
			ui->graphicsView_7->setPixmap(Mat2QImage(correctImg[1]));
			_activ_idx = 1;

			composePano();
		}
	}
	else
	{
		if (sender() == ui->graphicsView)
		{
			ui->doubleSpinBox_r1->setValue(arg);
			_activ_idx = 0;
		}
		else if (sender() == ui->graphicsView_2)
		{
			ui->doubleSpinBox_r2->setValue(arg);
			_activ_idx = 1;
		}
	}
}


void MainWindow::on_pushButton_save_clicked()
{
	cv::FileStorage fc;
	fc.open(commonParamPath + "/common.xml", cv::FileStorage::WRITE);

	if (fc.isOpened())
	{
		fc << "correctCurve" << _mapCurve;
		fc << "halfFov" << _halfFov;
		fc << "caliScale" << _scale;
		fc << "fuseBand" << _fuseBand;
		fc << "cropRatio" << ui->doubleSpinBox_cropRatio->value();
		fc << "stitchRoiW" << ui->doubleSpinBox_roi_w->value();
		fc << "stitchRoiH" << ui->doubleSpinBox_roi_h->value();

		fc.release();
	}

	//��������궨����
	cv::FileStorage fp;
	fp.open(QProPath.toStdString() + "/calibration_2cam.xml", cv::FileStorage::WRITE);

	if (fp.isOpened())
	{
		// �洢Բ��Ϣ
		fp << "imgParam" << "[";
		fp << "{:" << "param1" << "[:";
		fp << ui->doubleSpinBox_x1->value();
		fp << ui->doubleSpinBox_y1->value();
		fp << ui->doubleSpinBox_r1->value();
		fp << ui->doubleSpinBox_rot1->value();			
		fp << "]";
		fp << "param2" << "[:";
		fp << ui->doubleSpinBox_x2->value();
		fp << ui->doubleSpinBox_y2->value();
		fp << ui->doubleSpinBox_r2->value();
		fp << ui->doubleSpinBox_rot2->value();		
		fp << "]" << "}" << "]";

		fp.release();

		if (lang == english)
		{
			ui->label_currentState->setText("parameters are saved.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�궨�����ѱ���."));
		}
	
		ui->pushButton_testOnline->setEnabled(true);
	}	

	
}


void MainWindow::on_pushButton_load_clicked()
{
	//����calibration����
	FileStorage fp;
	fp.open(QProPath.toStdString() + "/calibration_2cam.xml", cv::FileStorage::READ);

	if (fp.isOpened())
	{
		FileNode cnode = fp["imgParam"];
		FileNodeIterator iter = cnode.begin();
		FileNodeIterator iter_end = cnode.end();

		for (; iter != iter_end; iter++)
		{
			vector<double> arr;
			(*iter)["param1"] >> arr;
			ui->doubleSpinBox_x1->setValue(arr[0]); ui->doubleSpinBox_y1->setValue(arr[1]); ui->doubleSpinBox_r1->setValue(arr[2]);
			ui->doubleSpinBox_rot1->setValue(arr[3]); 
			arr.clear();

			(*iter)["param2"] >> arr;
			ui->doubleSpinBox_x2->setValue(arr[0]); ui->doubleSpinBox_y2->setValue(arr[1]); ui->doubleSpinBox_r2->setValue(arr[2]); 
			ui->doubleSpinBox_rot2->setValue(arr[3]); 
			arr.clear();
		}

		fp.release();

		if (lang == english)
		{
			ui->label_currentState->setText("parameters are loaded.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�궨����������."));
		}

		on_pushButton_render_clicked();

		ui->pushButton_testOnline->setEnabled(true);
	}
	else
	{
		if (lang == english)
		{
			ui->label_currentState->setText("can not open the \"calibration_2cam.xml\" file!");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�޷��ҵ�\"calibration_2cam.xml\"�����ļ�."));
		}
	}

}


void MainWindow::on_pushButton_upload_clicked()
{
	bool f1 = false, f2 = false;

	if (uploadFile("calibration_2cam.xml"))
	{
		f1 = true;
	}
	

	if (uploadFile("camera.xml"))
	{
		f2 = true;
	}

	if (f1 && f2)
	{
		if (lang == english)
		{
			ui->label_currentState->setText("calibration file upload successful.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�궨�ļ��ϴ��ɹ�."));
		}
	}
	else
	{
		if (lang == english)
		{
			ui->label_currentState->setText("calibration file upload failed! Please retry.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�궨�ļ��ϴ�ʧ�ܣ�������."));
		}
	}
	
}


bool MainWindow::uploadFile(const QString& file)
{
	//׼���ļ�
	QFile xml_file(QProPath + "/" + file);
	xml_file.open(QIODevice::ReadOnly);
	int file_lenth = xml_file.size();
	QDataStream in(&xml_file);
	char* buf = new char[file_lenth];
	in.readRawData(buf, file_lenth);
	xml_file.close();

	//׼��ͷ��Ϣ
	QNetworkRequest netRequest;
	netRequest.setUrl(QUrl(camHttpAdress + file));
	netRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
	netRequest.setRawHeader("filename", xml_file.fileName().toUtf8());

	//׼������
	QByteArray arr = QByteArray(buf, file_lenth);
	m_pNetworkReply = m_pNetworkManager->post(netRequest, arr);

	// 	connect(m_pNetworkReply, SIGNAL(finished()), this, SLOT(uploadFinished()));

	QEventLoop eventloop;
	connect(m_pNetworkReply, SIGNAL(finished()), &eventloop, SLOT(quit())); //��������ź�		
	eventloop.exec();

	int status = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (status == 200)
	{
		return true;
	}
	else
	{
		return false;
	}
}



void MainWindow::readMaps()
{
	bool f1 = false, f2 = false;

	ifstream fmapx(commonParamPath + "/mapX.bin", std::ios::binary);
	if (fmapx.is_open())
	{
		fmapx.read((char*)mapX.data, sizeof(float)*mapX.rows*mapX.cols);
		fmapx.close();
	}
	else
	{
		qWarning() << "can not find mapX";
		f1 = true;
	}

	ifstream fmapy(commonParamPath + "/mapY.bin", std::ios::binary);
	if (fmapy.is_open())
	{
		fmapy.read((char*)mapY.data, sizeof(float)*mapY.rows*mapY.cols);
		fmapy.close();
	}
	else
	{
		qWarning() << "can not find mapY";
		f2 = true;
	}

	if (f1 || f2)
	{
		//���ȸ��±�׼��һ������
		calcStandardMap(Size2i(CALIB_SIZE * 2, CALIB_SIZE), mapX, mapY, _mapCurve, _halfFov*PI_OVER_180, PI_2, 0);

		//����У��map
		std::ofstream fmapx(commonParamPath + "/mapX.bin", std::ios::binary | std::ios::trunc);
		fmapx.write((char*)mapX.data, sizeof(float)*mapX.rows*mapX.cols);
		fmapx.close();

		std::ofstream fmapy(commonParamPath + "/mapY.bin", std::ios::binary | std::ios::trunc);
		fmapy.write((char*)mapY.data, sizeof(float)*mapY.rows*mapY.cols);
		fmapy.close();

		if (lang == english)
		{
			ui->label_currentState->setText("maps are updated.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("ӳ�����³ɹ�."));
		}
	}
}


void MainWindow::readHDMaps()
{
	bool f1 = false, f2 = false;

	ifstream fmapx(commonParamPath + "/HDmapX.bin", std::ios::binary);
	if (fmapx.is_open())
	{
		fmapx.read((char*)HDmapX.data, sizeof(float)*HDmapX.rows*HDmapX.cols);
		fmapx.close();
	}
	else
	{
		qWarning() << "can not find HDmapX";
		f1 = true;
	}

	ifstream fmapy(commonParamPath + "/HDmapY.bin", std::ios::binary);
	if (fmapy.is_open())
	{
		fmapy.read((char*)HDmapY.data, sizeof(float)*HDmapY.rows*HDmapY.cols);
		fmapy.close();
	}
	else
	{
		qWarning() << "can not find HDmapY";
		f2 = true;
	}

	if (f1 || f2)
	{
		//���ȸ��±�׼��һ������
		calcStandardMap(Size2i(FULL_SIZE * 2, FULL_SIZE), HDmapX, HDmapY, _mapCurve, _halfFov*PI_OVER_180, PI_2, 0);

		//����У��map
		std::ofstream fmapx(commonParamPath + "/HDmapX.bin", std::ios::binary | std::ios::trunc);
		fmapx.write((char*)HDmapX.data, sizeof(float)*HDmapX.rows*HDmapX.cols);
		fmapx.close();

		std::ofstream fmapy(commonParamPath + "/HDmapY.bin", std::ios::binary | std::ios::trunc);
		fmapy.write((char*)HDmapY.data, sizeof(float)*HDmapY.rows*HDmapY.cols);
		fmapy.close();

		if (lang == english)
		{
			ui->label_currentState->setText("maps are updated.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("ӳ�����³ɹ�."));
		}
	}
}


void MainWindow::readMasks()
{
	//����mask img
	cutMask = imread(commonParamPath + "/cut_mask.jpg", CV_LOAD_IMAGE_GRAYSCALE);//�˴����뱣֤mask�ǵ�ͨ����
	cutMask_2 = imread(commonParamPath + "/cut_mask_2.jpg", CV_LOAD_IMAGE_GRAYSCALE);//�˴����뱣֤mask�ǵ�ͨ����

	if (cutMask.empty() || cutMask.size() != Size(CALIB_SIZE * 2, CALIB_SIZE) || cutMask_2.empty() || cutMask_2.size() != Size(CALIB_SIZE * 2, CALIB_SIZE))
	{
		qWarning() << "can not find enough masks!";

		cutMask = Mat(CALIB_SIZE, CALIB_SIZE * 2, CV_8UC1, Scalar::all(255));
		cutMask_2 = Mat(CALIB_SIZE, CALIB_SIZE * 2, CV_8UC1, Scalar::all(255));

		Mat mask(CALIB_SIZE, CALIB_SIZE * 2, CV_8UC1, Scalar::all(255));
		//------------------------cutMask����----------------------------

		imgSlopeEdge(cutMask, cutMask.cols*0.25, _fuseBand, VERTICAL_LEFT, mask);
		imgSlopeEdge(mask, cutMask.cols*0.75, _fuseBand, VERTICAL_RIGHT, cutMask);

		imgSlopeEdge(cutMask_2, cutMask_2.cols*0.25, 0, VERTICAL_LEFT, mask);
		imgSlopeEdge(mask, cutMask_2.cols*0.75, 0, VERTICAL_RIGHT, cutMask_2);

		imwrite(commonParamPath + "/cut_mask.jpg", cutMask);
		imwrite(commonParamPath + "/cut_mask_2.jpg", cutMask_2);

		if (lang == english)
		{
			ui->label_currentState->setText("mask images are updated.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("��ģͼ����³ɹ�."));
		}
	}
}


void MainWindow::readCommonParams()
{
	//����calibration����
	FileStorage fc;
	fc.open(commonParamPath + "/common.xml", cv::FileStorage::READ);

	if (fc.isOpened())
	{
		double val;

		fc["correctCurve"] >> _mapCurve;

		fc["halfFov"] >> _halfFov;

		fc["fuseBand"] >> _fuseBand;

		fc["cropRatio"] >> val;
		ui->doubleSpinBox_cropRatio->setValue(val);

		fc["stitchRoiW"] >> val;
		ui->doubleSpinBox_roi_w->setValue(val);

		fc["stitchRoiH"] >> val;
		ui->doubleSpinBox_roi_h->setValue(val);

		fc.release();

	}
	else
	{
		if (lang == english)
		{
			ui->label_currentState->setText("Can not find the \"common xml\" file !");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�޷��ҵ�\"common xml\"�ļ�."));
		}
	}

}


void MainWindow::on_pushButton_openPano_clicked()
{
	QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QProPath,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	vector<QString> abPath, filename;
	string imagePath;

	if (filePath != "")
	{
		QDir dir(filePath);  QStringList filters;
		filters << QString("*.jpeg") << QString("*.jpg") << QString("*.png") << QString("*.tiff") << QString("*.gif") << QString("*.bmp")
			<< QString("*.JPG") << QString("*.PNG") << QString("*.TIFF") << QString("*.GIF") << QString("*.BMP");
		dir.setFilter(QDir::Files | QDir::NoSymLinks);
		dir.setNameFilters(filters);
		QFileInfoList list = dir.entryInfoList();
		int file_count = list.count();
		if (file_count < 1)
		{
			if (lang == english)
			{
				ui->label_currentState->setText("There is no enough images! Please retry!");
			}
			else
			{
				ui->label_currentState->setText(QString::fromLocal8Bit("û���㹻��ͼƬ�ɹ�ѡ��������."));
			}
			return;
		}
		int count = 0;
		for (int index = 0; index < file_count; index++)
		{
			QFileInfo file_info = list.at(index);

			abPath.push_back(file_info.absoluteFilePath());
			filename.push_back(file_info.fileName());
			count++;
		}

		if (count < 1)
		{
			if (lang == english)
			{
				ui->label_currentState->setText("can not load enough images! Please retry!");
			}
			else
			{
				ui->label_currentState->setText(QString::fromLocal8Bit("�޷������㹻��ͼ��������."));
			}
			return;
		}

		FolderImgs *m_dlg = new FolderImgs(this);
		m_dlg->setInfo(abPath, filename, count);
		m_dlg->Init();
		int lRet = m_dlg->exec();
		if (lRet == FolderImgs::Accepted)
		{
			imagePath = m_dlg->path[0];
		}
		else
		{
			if (lang == english)
			{
				ui->label_currentState->setText("an error occured when open files!");
			}
			else
			{
				ui->label_currentState->setText(QString::fromLocal8Bit("���ļ�ʱ��������."));
			}
			return;
		}

		Mat anotherPano = imread(imagePath);

		ui->graphicsView_pano->setPixmap((Mat2QImage(anotherPano)));

		_renderWindow->updatePanoImg(anotherPano);
		_renderWindow->setWindowTitle(QString::fromLocal8Bit("��Ⱦ���"));

		_renderWindow->show();

	}
}


//====================�Զ�ƴ��===================
void MainWindow::on_pushButton_autoStitch_clicked()
{
	if (lang == english)
	{
		ui->label_currentState->setText("auto stitching begin ...");
	}
	else
	{
		ui->label_currentState->setText(QString::fromLocal8Bit("�Զ�ƴ�ӿ�ʼ ..."));
	}
	int64 tic = cvGetTickCount();

	//step 1: ��У����ͼ���вü�����ƴ��ͼ��
	Mat img[IMG_NUM];

	float crop_ratio = ui->doubleSpinBox_cropRatio->value();

	for (int i = 0; i < IMG_NUM; ++i)
	{
		img[i] = correctImg[i].colRange(correctImg[i].cols*crop_ratio, correctImg[i].cols*(1.0 - crop_ratio));
	}

	vector<Mat> imgs;

	imgs.push_back(img[0].colRange(img[0].cols*0.5, img[0].cols));
	imgs.push_back(img[1]);
	imgs.push_back(img[0].colRange(0, img[0].cols*0.5));

	//step 2: ����stitcher����ƴ��
	float col_ratio = ui->doubleSpinBox_roi_w->value(); //���0.5, Ŀǰ������ֵӦΪ0.375
	float row_ratio = ui->doubleSpinBox_roi_h->value();

	vector<vector<Rect> > rois;
	vector<Rect> roi0, roi1, roi2;
	roi0.push_back(Rect(Point(imgs[0].cols*(1.0 - col_ratio * 2), imgs[0].rows*row_ratio), Point(imgs[0].cols, imgs[0].rows*(1.0 - row_ratio))));
	roi1.push_back(Rect(Point(0, imgs[1].rows*row_ratio), Point(imgs[1].cols*col_ratio, imgs[1].rows*(1.0 - row_ratio))));
	roi1.push_back(Rect(Point(imgs[1].cols*(1.0 - col_ratio), imgs[1].rows*row_ratio), Point(imgs[1].cols, imgs[1].rows*(1.0 - row_ratio))));
	roi2.push_back(Rect(Point(0, imgs[2].rows*row_ratio), Point(imgs[2].cols*col_ratio * 2, imgs[2].rows*(1.0 - row_ratio))));

	rois.push_back(roi0); rois.push_back(roi1); rois.push_back(roi2); 

	double sitich_scale = ui->doubleSpinBox_workScale->value();
	double seam_scale = ui->doubleSpinBox_seamScale->value();

	Mat stitchPano;

	if (!imgStitcher(imgs, stitchPano, rois, sitich_scale, seam_scale, 5, QProPath.toStdString() + "/camera.xml", 0.3, true, true, true, _showDebugImg))
	{
		if (lang == english)
		{
			ui->label_currentState->setText("can not stitch images, some errer occered, please retry!");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�޷����ƴ�ӣ��������������ԣ�"));
		}
		return;
	}

	if (_showDebugImg)
	{
// 		showImg("ԭʼƴ��", stitchPano, 0.25);
		imwrite(QProPath.toStdString() + "/panorama_ori.jpg", stitchPano);
	}

	//step 3: warp
	imgWarp(stitchPano, _panoStitch, Size(CALIB_SIZE * 2, CALIB_SIZE), ui->spinBox_conerRange->value(), 5, 10, _showDebugImg);

	showImg("����ƴ��", _panoStitch, 0.5);
	imwrite(QProPath.toStdString() + "/panorama.jpg", _panoStitch);

	_renderWindow->updatePanoImg(_panoStitch);
	_renderWindow->setWindowTitle(QString::fromLocal8Bit("��ȾԤ��-�ںϽ��"));
	_renderWindow->show();

	int64 toc = cvGetTickCount();
	if (lang == english)
	{
		ui->label_currentState->setText("auto-stitch accomplished, time elapsed: " + QString::number(double(toc - tic) / getTickFrequency()) + " s. ");
	}
	else
	{
		ui->label_currentState->setText(QString::fromLocal8Bit("�Զ�ƴ����ɣ���ʱ�� ") + QString::number(double(toc - tic) / getTickFrequency()) + " s. ");
	}

}


void MainWindow::updateIndividualMaps(int idx)
{
	if (idx<0)
	{
		calcIndividualMap(mapX, mapY, smapX[0], smapY[0], ui->doubleSpinBox_rot1->value()*PI_OVER_180,
			ui->doubleSpinBox_x1->value(), ui->doubleSpinBox_y1->value(), ui->doubleSpinBox_r1->value());

		calcIndividualMap(mapX, mapY, smapX[1], smapY[1], ui->doubleSpinBox_rot2->value()*PI_OVER_180,
			ui->doubleSpinBox_x2->value(), ui->doubleSpinBox_y2->value(), ui->doubleSpinBox_r2->value());
	}
	else
	{
		switch (idx)
		{
		case 0:
		{
			calcIndividualMap(mapX, mapY, smapX[idx], smapY[idx], ui->doubleSpinBox_rot1->value()*PI_OVER_180,
				ui->doubleSpinBox_x1->value(), ui->doubleSpinBox_y1->value(), ui->doubleSpinBox_r1->value());
			break;
		}
		case 1:
		{
			calcIndividualMap(mapX, mapY, smapX[idx], smapY[idx], ui->doubleSpinBox_rot2->value()*PI_OVER_180,
				ui->doubleSpinBox_x2->value(), ui->doubleSpinBox_y2->value(), ui->doubleSpinBox_r2->value());
			break;
		}

		}
	}
	
}


void MainWindow::addMarkers(InputArray in)
{
	Mat backImg = in.getMat();

	int len_width = 2;
	int len_width_2 = 1;
	Scalar color(255, 0, 0);
	Scalar color_2(0, 0, 255);
	Scalar color_3(0, 255, 0);

	int len_type = CV_AA;

	//����
// 	line(backImg, Point(backImg.cols / 2, 0), Point(backImg.cols / 2, backImg.rows), color, len_width_2, len_type);
	line(backImg, Point(backImg.cols *0.32, 0), Point(backImg.cols *0.32, backImg.rows), color_3, len_width, len_type);
	line(backImg, Point(backImg.cols * 0.68, 0), Point(backImg.cols * 0.68, backImg.rows), color_3, len_width, len_type);

	//����
	line(backImg, Point(0, backImg.rows / 2), Point(backImg.cols, backImg.rows / 2), color_2, len_width, len_type);
	line(backImg, Point(0, backImg.rows*S_25_OVER_180), Point(backImg.cols, backImg.rows*S_25_OVER_180), color_2, len_width, len_type);
	line(backImg, Point(0, backImg.rows*(1.0 - S_25_OVER_180)), Point(backImg.cols, backImg.rows*(1.0 - S_25_OVER_180)), color_2, len_width, len_type);
}


//------------------------ͼ�����м����----------------------------

void MainWindow::imgProcessFromMotion(QPointF center, double r, double ang, int idx)
{
	calcIndividualMap(mapX, mapY, smapX[idx], smapY[idx], ang*PI_OVER_180, center.x()*_scale, center.y()*_scale, r*_scale);
	remap(scaleSrcImg[idx], correctImg[idx], smapX[idx], smapY[idx], IMG_INTER_METHOD);

	addMarkers(correctImg[idx]);
	
	imgMaskFilter(correctImg[idx], cutMask, maskImg[idx]);
	imgHorizontalMove(maskImg[idx], stitchImg[idx], stitchImg[idx].cols*(0.5 + 0.5*idx));

	//��Ա궨��������
	imgMaskFilter(correctImg[idx], cutMask_2, maskImg[idx]);
	imgHorizontalMove(maskImg[idx], stitchImg_2[idx], stitchImg_2[idx].cols*(0.5 + 0.5*idx));
}


bool MainWindow::captureImg(const QString& path, bool update)
{
	cout << "====================================================" << endl;

	bool is_cap_succeed = false;

	if (path != "")
	{
		if (postOrderToCam(camCommandList[PHOTO_MODE])) //����ɹ��л������ģʽ
		{
			if (lang == english)
			{
				ui->label_currentState->setText("connect Success, please wait for image capture...");
			}
			else
			{
				ui->label_currentState->setText(QString::fromLocal8Bit("���ӳɹ�����ȴ����� ..."));
			}

			if (postOrderToCam(camCommandList[START_PHOTO])) //����ɹ������������
			{
				if (lang == english)
				{
					ui->label_currentState->setText("capture Success, please wait for image fetch...");
				}
				else
				{
					ui->label_currentState->setText(QString::fromLocal8Bit("���ճɹ�����ȴ�ȡͼ ..."));
				}
				int64 tic = cvGetTickCount();

				//===========����ͼ��������xml============
				QByteArray byte_data = m_pNetworkReply->readAll();

				QString errStr;
				int errLine, errCol;

				QDomDocument doc;

				if (!doc.setContent(byte_data, false, &errStr, &errLine, &errCol))
				{
					if (lang == english)
					{
						ui->label_currentState->setText("xml parse false");
					}
					else
					{
						ui->label_currentState->setText(QString::fromLocal8Bit("xml ����ʧ��."));
					}
				}

				if (doc.isNull())
				{
					if (lang == english)
					{
						ui->label_currentState->setText("xml is not exit");
					}
					else
					{
						ui->label_currentState->setText(QString::fromLocal8Bit("xml ������."));
					}
				}

				QDomElement root = doc.documentElement();//

				QDomNodeList list = root.childNodes();

				QString src_img_name;

				int left_pic_num;

				for (int i = 0; i < list.size(); ++i)
				{
					QDomNode node = list.at(i);

					if (node.nodeName() == "File")
					{
						QDomNode img_name = node.firstChild();
						if (img_name.nodeName() == "NAME")
						{
							src_img_name = img_name.toElement().text();
// 							break;
						}
					}

					if (node.nodeName() == "FREEPICNUM")
					{
						left_pic_num = node.toElement().text().toInt();
					}
				}

				cout << "sd��ʣ��������������Ƭ������" << left_pic_num << endl;

				if (src_img_name.size() > 0) //˵���ɹ���ȡ����һ��ͼ�������
				{
					qDebug() << "initial image name: " + src_img_name;

					bool first_fetch_succed = false, second_fetch_succed = false;

					if (src_img_name.at(15) == 'A') //˵��������˳��
					{
						//ȡ��һ��ͼ
						if (fetchImgFromCam(path, src_img_name, 1))
						{
							first_fetch_succed = true;
							if (lang == english)
							{
								ui->label_currentState->setText("first image fetched Successfully. ");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("��һ��ͼȡͼ�ɹ�, ��ȴ�ȡ�ڶ���ͼ ..."));
							}

						}
						else
						{
							if (lang == english)
							{
								ui->label_currentState->setText("first image fetched false.");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("��һ��ͼȡͼʧ��."));
							}
						}

						//ȡ�ڶ���ͼ
						QString secondImgName = src_img_name.replace(15, 1, "B");
						int k = 0;
						while (!second_fetch_succed && k < 3)
						{
							k++;
							if (fetchImgFromCam(path, secondImgName, 1))
							{
								second_fetch_succed = true;
							}
							secondImgName = nameGenerator(secondImgName, 1);
						}

						if (second_fetch_succed)
						{
							if (lang == english)
							{
								ui->label_currentState->setText("second image fetched Successfully. ");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("�ڶ���ͼȡͼ�ɹ�."));
							}
						}
						else
						{
							if (lang == english)
							{
								ui->label_currentState->setText("second image fetched false.");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("�ڶ���ͼȡͼʧ��."));
							}
						}

					}
					else //˵���������ȸ����˵ڶ���ͼ������
					{
						//ȡ��һ��ͼ
						QString firstImgName = src_img_name;
						firstImgName.replace(15, 1, "A");

						int k = 0;
						while (!first_fetch_succed && k < 3)
						{
							k++;
							if (fetchImgFromCam(path, firstImgName, 1))
							{
								first_fetch_succed = true;
							}
							firstImgName = nameGenerator(firstImgName, -1);
						}

						if (first_fetch_succed)
						{
							if (lang == english)
							{
								ui->label_currentState->setText("first image fetched Successfully. ");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("��һ��ͼȡͼ�ɹ�, ��ȴ�ȡ�ڶ���ͼ ..."));
							}
						}
						else
						{
							if (lang == english)
							{
								ui->label_currentState->setText("first image fetched false.");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("��һ��ͼȡͼʧ��."));
							}
						}

						//ȡ�ڶ���ͼ
						if (fetchImgFromCam(path, src_img_name, 1))
						{
							second_fetch_succed = true;
							if (lang == english)
							{
								ui->label_currentState->setText("second image fetched Successfully. ");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("�ڶ���ͼȡͼ�ɹ�."));
							}
						}
						else
						{
							if (lang == english)
							{
								ui->label_currentState->setText("second image fetched false.");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("�ڶ���ͼȡͼʧ��."));
							}
						}

					}

					int64 toc = cvGetTickCount();
					cout << "image fetch time: " + QString::number(double(toc - tic) / getTickFrequency()).toStdString() + " s. " << endl;

					if (first_fetch_succed && second_fetch_succed)
					{
						if (update)
						{
							srcImg[0] = imread(path.toStdString() + "/Image1.jpg");
							srcImg[1] = imread(path.toStdString() + "/Image2.jpg");

							//----------------------------------------------
							//���ŵ�С�ߴ������궨�����Լ���ʵʱ��
							cv::resize(srcImg[0], scaleSrcImg[0], Size(), _scale, _scale);	
							cv::resize(srcImg[1], scaleSrcImg[1], Size(), _scale, _scale);

							firstRun = true;

							ui->graphicsView->setPixmap(Mat2QImage(srcImg[0]));
							ui->graphicsView_2->setPixmap(Mat2QImage(srcImg[1]));

							if (lang == english)
							{
								ui->label_currentState->setText("src-images are captured successful, time elapsed: " + QString::number(double(toc - tic) / getTickFrequency()) + " s, please calibrate. ");
							}
							else
							{
								ui->label_currentState->setText(QString::fromLocal8Bit("ͼ������ȡͼ�ɹ�������ʱ��") +
									QString::number(double(toc - tic) / getTickFrequency()) + QString::fromLocal8Bit("�룬��궨."));
							}

							ui->groupBox_left->setEnabled(true);
							ui->groupBox_right->setEnabled(true);
							ui->groupBox_preview->setEnabled(true);
							ui->groupBox_save->setEnabled(true);

							ui->pushButton_load->setStyleSheet("background-color: rgb(55, 55, 55);");
							ui->pushButton_render->setStyleSheet("background-color: rgb(55, 55, 55);");
							ui->pushButton_mode->setStyleSheet("background-color: rgb(55, 55, 55);");

						}

						is_cap_succeed = true;
					}
				}
				else
				{
					if (lang == english)
					{
						ui->label_currentState->setText("image name is null! ");
					}
					else
					{
						ui->label_currentState->setText(QString::fromLocal8Bit("ͼ��Ϊ��."));
					}
				}
			}
			else
			{
				if (lang == english)
				{
					ui->label_currentState->setText("capture false! ");
				}
				else
				{
					ui->label_currentState->setText(QString::fromLocal8Bit("����ʧ��."));
				}
			}
		}
		else
		{
			if (lang == english)
			{
				ui->label_currentState->setText("connect false! ");
			}
			else
			{
				ui->label_currentState->setText(QString::fromLocal8Bit("����ʧ��."));
			}
		}
	}

	return is_cap_succeed;
}


void MainWindow::on_pushButton_cam_clicked()
{
	QProPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../data",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	testPath = QProPath + "/test";
	QDir tpath(testPath);
	if (!tpath.exists())
	{
		_mkdir(testPath.toStdString().c_str());
	}

	if (QProPath != "")
	{
		this->setWindowTitle(QString::fromLocal8Bit("���ھ۴�IPANOȫ������궨��� - ") + QProPath);
		ui->label_Test->setText("");
		ui->label_App->setText("");
		ui->label_Cloud->setText("");
	}

	if (lang == english)
	{
		ui->label_currentState->setText("connecting camera, please wait ... ");
	}
	else
	{
		ui->label_currentState->setText(QString::fromLocal8Bit("��������У���ȴ� ..."));
	}

	captureImg(QProPath, true);

}


QString MainWindow::nameGenerator(const QString& imName, int secs)
{
	//�滻�ַ������ٴ���ȡ�ڶ���ͼ
	QString newName = imName;

	QString hours = newName.mid(9, 2);
	QString minites = newName.mid(11, 2);
	QString seconds = newName.mid(13, 2);

	bool num_ok;

	int hours_num = hours.toInt(&num_ok, 10);
	int minites_num = minites.toInt(&num_ok, 10);
	int seconds_num = seconds.toInt(&num_ok, 10);

	QTime time0(hours_num, minites_num, seconds_num);

	QTime time1 = time0.addSecs(secs);

	QString timeStr = time1.toString("hhmmss");

	newName.replace(9, 6, timeStr);

	return newName;
}


bool MainWindow::postOrderToCam(const QString& command)
{
	QNetworkRequest netRequest;
	netRequest.setUrl(QUrl(command)); //��������

	m_pNetworkReply = m_pNetworkManager->get(netRequest);

	QEventLoop eventloop;
	connect(m_pNetworkReply, SIGNAL(finished()), &eventloop, SLOT(quit())); //��������ź�		
	eventloop.exec();

	int status = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (status == 200)
	{
		return true;
	}

	return false;
}


bool MainWindow::requestImgFromCam(const QString& imName)
{
	QNetworkRequest netRequest;
	netRequest.setUrl(QUrl(camHttpAdress + "NOVATEK/PHOTO/" + imName)); //ȡͼ

	m_pNetworkReply = m_pNetworkManager->get(netRequest);

	QEventLoop eventloop;
	connect(m_pNetworkReply, SIGNAL(finished()), &eventloop, SLOT(quit())); //��������ź�		
	eventloop.exec();

	int status = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (status == 200) //����http���ӳɹ������ҵ���Դ��������Դ�������Ƿ�����޷�ȷ��
	{
		return true;
	}

	return false;
}


bool MainWindow::fetchImgFromCam(const QString& path, const QString& imName, int counter)
{
	bool flag = false;

	if (requestImgFromCam(imName)) // ���ͼ������ɹ�
	{
		qDebug() << imName;

		int req_count = 0;
		while (req_count < counter)
		{
			req_count++;

			cout << "fetch times: " << req_count << endl;

			QByteArray img_byte = m_pNetworkReply->readAll();

			QString imgXml(img_byte);

			int index = imgXml.indexOf("Page Not found"); //�����ж��Ƿ�ɹ���ȡͼƬ

			if (index < 0)
			{
				if (imName.at(15) == 'A')
				{
					writeImgs(path + "/Image1.jpg", img_byte);
				}
				else if (imName.at(15) == 'B')
				{
					writeImgs(path + "/Image2.jpg", img_byte);
				}

				flag = true;
				break;
			}

			requestImgFromCam(imName);
		}
	}

	return flag;
}


inline void MainWindow::writeImgs(const QString& name, QByteArray& data)
{
	QFile file(name);
	file.open(QIODevice::WriteOnly);
	file.write(data);
	file.close();
}


void MainWindow::requestTimeout()
{
	if (lang == english)
	{
		ui->label_currentState->setText("time out");
	}
	else
	{
		ui->label_currentState->setText(QString::fromLocal8Bit("�����ѳ�ʱ."));
	}
}


void MainWindow::on_pushButton_showDebug_clicked()
{
	_showDebugImg = !_showDebugImg;
	if (_showDebugImg)
	{
		ui->pushButton_showDebug->setStyleSheet("background-color: rgb(55, 55, 55);");
	}
	else
	{
		ui->pushButton_showDebug->setStyleSheet("background-color: rgb(155, 155, 155);");
		destroyWindow("ԭʼƴ��");
		destroyWindow("ƥ��ͼ��0-1");
		destroyWindow("ƥ��ͼ��1-2");
	}

}


void MainWindow::on_pushButton_sd_clear_clicked()
{
	if (postOrderToCam(camCommandList[CLEAR_SD])) //����ɹ������������
	{
		//===========����ͼ��������xml============
		QByteArray byte_data = m_pNetworkReply->readAll();

		QString errStr;
		int errLine, errCol;

		QDomDocument doc;

		if (!doc.setContent(byte_data, false, &errStr, &errLine, &errCol))
		{
			if (lang == english)
			{
				ui->label_Test->setText("xml parse false");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("xml ����ʧ��."));
			}
		}

		if (doc.isNull())
		{
			if (lang == english)
			{
				ui->label_Test->setText("xml is not exit");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("xml ������."));
			}
		}

		QDomElement root = doc.documentElement();//

		QDomNodeList list = root.childNodes();

		int remove_status;

		for (int i = 0; i < list.size(); ++i)
		{
			QDomNode node = list.at(i);

			if (node.nodeName() == "Status")
			{
				remove_status = node.toElement().text().toInt();
			}
		}

		if (remove_status == 0)
		{
			if (lang == english)
			{
				ui->label_Test->setText("all pictures and movies are removed.");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("���е�ͼ�����Ƶ�ļ������"));
			}
		}
		else
		{
			if (lang == english)
			{
				ui->label_Test->setText("remove sd card failed.");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("�洢��ɾ��ʧ��"));
			}
		}
		
	}
	else
	{
		if (lang == english)
		{
			ui->label_Test->setText("delete instruction transfer failed.");
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("ɾ������δ�ɹ�����."));
		}
	}
}


void MainWindow::on_pushButton_get_sd_volume_clicked()
{
	if (postOrderToCam(camCommandList[GET_FREE_SPACE])) //����ɹ������������
	{
		//===========����ͼ��������xml============
		QByteArray byte_data = m_pNetworkReply->readAll();

		QString errStr;
		int errLine, errCol;

		QDomDocument doc;

		if (!doc.setContent(byte_data, false, &errStr, &errLine, &errCol))
		{
			if (lang == english)
			{
				ui->label_Test->setText("xml parse false");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("xml ����ʧ��."));
			}
		}

		if (doc.isNull())
		{
			if (lang == english)
			{
				ui->label_Test->setText("xml is not exit");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("xml ������."));
			}
		}

		QDomElement root = doc.documentElement();//

		QDomNodeList list = root.childNodes();

		QString left_volume;

		for (int i = 0; i < list.size(); ++i)
		{
			QDomNode node = list.at(i);

			if (node.nodeName() == "Value")
			{
				left_volume = node.toElement().text();
			}
		}

		float vol = left_volume.toFloat()/1073741824;

		if (lang == english)
		{
			ui->label_Test->setText("Memery space left: " + QString("%2").arg(vol) +" G bytes.");
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("�ڴ濨ʣ��������") + QString("%2").arg(vol) + " G bytes.");
		}
	}
	else
	{
		if (lang == english)
		{
			ui->label_Test->setText("Free-memery query failed.");
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("ʣ��������ѯʧ��."));
		}
	}
}


void MainWindow::on_pushButton_get_power_clicked()
{
	if (postOrderToCam(camCommandList[GET_BATTERY_STATUS])) //����ɹ������������
	{
		//===========����ͼ��������xml============
		QByteArray byte_data = m_pNetworkReply->readAll();

		QString errStr;
		int errLine, errCol;

		QDomDocument doc;

		if (!doc.setContent(byte_data, false, &errStr, &errLine, &errCol))
		{
			if (lang == english)
			{
				ui->label_Test->setText("xml parse false");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("xml ����ʧ��."));
			}
		}

		if (doc.isNull())
		{
			if (lang == english)
			{
				ui->label_Test->setText("xml is not exit");
			}
			else
			{
				ui->label_Test->setText(QString::fromLocal8Bit("xml ������."));
			}
		}

		QDomElement root = doc.documentElement();//

		QDomNodeList list = root.childNodes();

		int power_index = 6;

		for (int i = 0; i < list.size(); ++i)
		{
			QDomNode node = list.at(i);

			if (node.nodeName() == "Value")
			{
				power_index = node.toElement().text().toInt();
			}
		}


		if (lang == english)
		{
			ui->label_Test->setText("Power status : " + batteryStatus[power_index]);
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("���״̬��") + batteryStatus[power_index]);
		}
	}
	else
	{
		if (lang == english)
		{
			ui->label_Test->setText("battery status query failed.");
		}
		else
		{
			ui->label_Test->setText(QString::fromLocal8Bit("���״̬��ѯʧ��."));
		}
	}
}


void MainWindow::on_sliderReleased()
{
	int val = ui->horizontalSlider_ev->value();

	QString order = camHttpAdress + "?custom=1&cmd=2005&par=" + QString::number(12-val);

	if (postOrderToCam(order)) //����ɹ������������
	{
		if (lang == english)
		{
			ui->label_currentState->setText("exposure changed successful.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�ع�ֵ�����ɹ�."));
		}
	}
	else
	{
		if (lang == english)
		{
			ui->label_currentState->setText("exposure changed failed.");
		}
		else
		{
			ui->label_currentState->setText(QString::fromLocal8Bit("�ع�ֵ��������ʧ��."));
		}
	}
}